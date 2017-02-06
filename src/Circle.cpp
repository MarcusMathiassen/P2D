
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Circle.h"

#define PI 3.14159
#define HALF_PI 1.570796
#define DOUBLE_PI 6.283185
#define LOSSENERGY 0.99

vec<uptr<Circle>> object_vec;

Circle::Circle(const Vec2 &p, float r, int v)
    : m_pos(p), m_radi(r), m_vertices(v) {
  m_vel = Vec2(0, 0);
  m_mass = 1.33333 * PI * m_radi * m_radi * m_radi;

  if (color_random)
    ++uniCol;
  assignColor(m_color);
  m_temp_color = m_color;
  m_index = object_vec.size(); // Object index is it´s number in the vector.

  /* We setup a cos/sin table for the circles draw function for use later.*/
  m_cosineTable.reserve(m_vertices + 1);
  m_sineTable.reserve(m_vertices + 1);
  m_cosineTable[0] = m_radi;
  m_sineTable[0] = 0;
  for (int i = 1; i <= m_vertices; ++i) {
    m_cosineTable[i] = (m_radi * cos(i * DOUBLE_PI / m_vertices));
    m_sineTable[i] = (m_radi * sin(i * DOUBLE_PI / m_vertices));
  }
}

void Circle::draw() const {
  if ((use_quadtree || use_fixedgrid) && debug_mode) {
    glColor3ub(m_temp_color.r, m_temp_color.g, m_temp_color.b);
  } else
    glColor3ub(m_color.r, m_color.g, m_color.b);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(m_pos.x, m_pos.y);
  for (int i = 0; i <= m_vertices; ++i) {
    glVertex2f(m_pos.x + m_cosineTable[i], m_pos.y + m_sineTable[i]);
  }
  glEnd();

  if (direction) {
    debug();
    show_collision_box();
  }
}

void Circle::debug() const {
  // Draws lines showing the direction
  float angle = atan2(m_vel.y, m_vel.x);
  float ny = m_pos.y + m_radi * 2 * sin(angle);
  float nx = m_pos.x + m_radi * 2 * cos(angle);

  if ((use_quadtree || use_fixedgrid) && debug_mode) {
    glColor3ub(m_temp_color.r, m_temp_color.g, m_temp_color.b);
  } else
    glColor3ub(m_color.r, m_color.g, m_color.b);
  glBegin(GL_LINES);
  glVertex2d(m_pos.x, m_pos.y);
  glVertex2d(nx, ny);
  glEnd();
}

void Circle::show_collision_box() const {
  // Draws collision boxes
  glColor3ub(0, 255, 0);
  glLineWidth(1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(m_pos.x - m_radi, m_pos.y - m_radi);
  glVertex2f(m_pos.x - m_radi, m_pos.y + m_radi);
  glVertex2f(m_pos.x + m_radi, m_pos.y + m_radi);
  glVertex2f(m_pos.x + m_radi, m_pos.y - m_radi);
  glEnd();
}

void Circle::update() {
  // Border collision check
  if (borderCol) {
    if (m_pos.x <= m_radi && m_vel.x < 0) {
      m_pos.x = (m_radi);
      m_vel.x = (-m_vel.x);
    }

    if (m_pos.x >= screen_width - m_radi && m_vel.x > 0) {
      m_pos.x = (screen_width - m_radi);
      m_vel.x = (-m_vel.x);
    }

    if (m_pos.y <= m_radi && m_vel.y < 0) {
      m_pos.y = (m_radi);
      m_vel.y = (-m_vel.y);
    }

    if (m_pos.y >= screen_height - m_radi && m_vel.y > 0) {
      m_pos.y = (screen_height - m_radi);
      m_vel.y = (-m_vel.y);
    }
  }

  float slow = 1.0;
  if (slowmotion)
    slow = 0.1;

  m_mass = m_radi;

  if (gravity)
    m_vel.y -= gravity_accel * m_mass * slow * dt;

  if (gravForce) {
    for (size_t i = 0; i < object_vec.size(); ++i) {
      gravitationforce(static_cast<Circle &>(*object_vec[i]));
    }
  }

  // Update ball position
  m_pos.x += (m_vel.x * slow * dt) * LOSSENERGY;
  m_pos.y += (m_vel.y * slow * dt) * LOSSENERGY;
}

bool Circle::collision_detection(const Circle &b) const {
  // Setup variables
  const Vec2 bpos = b.get_pos();
  const float bx = bpos.x;
  const float by = bpos.y;
  const float br = b.get_radi();

  //  basic square collision check
  if (m_pos.x - m_radi < bx + br && m_pos.x + m_radi > bx - br &&
      m_pos.y - m_radi < by + br && m_pos.y + m_radi > by - br) {

    // Circle collision check
    const float dx = bx - m_pos.x;
    const float dy = by - m_pos.y;
    const float sumRadius = m_radi + br;
    const float sqrRadius = sumRadius * sumRadius;

    const float distSqr = (dx * dx) + (dy * dy);

    if (distSqr <= sqrRadius)
      return true;
  }

  return false;
}

void Circle::collision_resolve(Circle &b) {
  // Setup variables
  const Vec2 bpos = b.get_pos();
  const Vec2 bvel = b.get_vel();

  const float bx = bpos.x;
  const float by = bpos.y;
  const float br = b.get_radi();
  const float m1 = m_mass;
  const float m2 = b.get_mass();

  const float dx = bx - m_pos.x;
  const float dy = by - m_pos.y;

  // collision depth
  const float colDepth = (m_radi + br) - sqrt(dx * dx + dy * dy);

  // contact angle
  const float colAngle = atan2(dy, dx);
  const float cos_angle = cos(colAngle);
  const float sin_angle = sin(colAngle);

  // move the balls away from eachother so they dont overlap
  const float a_move_x = -colDepth * 0.5 * cos_angle;
  const float a_move_y = -colDepth * 0.5 * sin_angle;
  const float b_move_x = colDepth * 0.5 * cos_angle;
  const float b_move_y = colDepth * 0.5 * sin_angle;

  if (m_pos.x + a_move_x >= m_radi &&
      m_pos.x + a_move_x <= screen_width - m_radi) {
    m_pos.x += (a_move_x);
  }
  if (m_pos.y + a_move_y >= m_radi &&
      m_pos.y + a_move_y <= screen_height - m_radi) {
    m_pos.y += (a_move_y);
  }
  if (bx + b_move_x >= br && bx + b_move_x <= screen_width - br) {
    b.add_pos_x(b_move_x);
  }
  if (by + b_move_y >= br && by + b_move_y <= screen_height - br) {
    b.add_pos_y(b_move_y);
  }

  const float vdx = bvel.x - m_vel.x;
  const float vdy = bvel.y - m_vel.y;
  const float d = dx * vdx + dy * vdy;

  if (d < 0) {
    Vec2 norm_vec(dx, dy);
    norm_vec = norm_vec.normalized();

    const Vec2 tang_vec((norm_vec.y * -1), norm_vec.x);

    const float scal_norm_1 = dot(norm_vec, m_vel);
    const float scal_norm_2 = dot(norm_vec, bvel);

    const float scal_tang_1 = dot(tang_vec, m_vel);
    const float scal_tang_2 = dot(tang_vec, bvel);
    const float scal_norm_1_after =
        (scal_norm_1 * (m1 - m2) + 2 * m2 * scal_norm_2) / (m1 + m2);
    const float scal_norm_2_after =
        (scal_norm_2 * (m2 - m1) + 2 * m1 * scal_norm_1) / (m1 + m2);

    const Vec2 scal_norm_1_after_vec(norm_vec * scal_norm_1_after);
    const Vec2 scal_norm_2_after_vec(norm_vec * scal_norm_2_after);

    const Vec2 scal_norm_1_vec(tang_vec * scal_tang_1);
    const Vec2 scal_norm_2_vec(tang_vec * scal_tang_2);

    set_vel((scal_norm_1_vec + scal_norm_1_after_vec) * LOSSENERGY);
    b.set_vel((scal_norm_2_vec + scal_norm_2_after_vec) * LOSSENERGY);
  }
}

void Circle::gravitationforce(const Circle &b) {
  // Set up variables
  Vec2 bpos = b.get_pos();
  float x1 = m_pos.x;
  float x2 = bpos.x;
  float y1 = m_pos.y;
  float y2 = bpos.y;

  // Mass of the balls.
  float m1 = m_mass;
  float m2 = b.get_mass();

  // Get distance between balls.
  float dx = x2 - x1;
  float dy = y2 - y1;
  float d = sqrt(dx * dx + dy * dy);

  if (d != 0) {

    float angle = atan2(dy, dx);
    const float G = 6.674e-5;
    float F = G * m1 * m2 / d * d;

    m_vel.x += F * cos(angle);
    m_vel.y += F * sin(angle);
  }
}

int Circle::get_index() const { return m_index; }
Vec2 Circle::get_pos() const { return m_pos; }
void Circle::add_pos_x(float f) { m_pos.x += f; }
void Circle::add_pos_y(float f) { m_pos.y += f; }
Vec2 Circle::get_vel() const { return m_vel; }
void Circle::set_vel(float x, float y) { m_vel.x = x, m_vel.y = y; }
void Circle::set_vel(const Vec2 &v) { m_vel.x = v.x, m_vel.y = v.y; }
void Circle::add_vel(float x, float y) { m_vel.x += x, m_vel.y += y; }
void Circle::add_vel_x(float f) { m_vel.x += f; }
void Circle::add_vel_y(float f) { m_vel.y += f; }
float Circle::get_mass() const { return m_mass; }
float Circle::get_radi() const { return m_radi; }
int Circle::get_vertices() const { return m_vertices; }
Color Circle::get_color() const { return m_color; }
void Circle::set_temp_color(const Color &c) { m_temp_color = c; }
