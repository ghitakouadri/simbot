#ifndef ROBOT_H
#define ROBOT_H

struct Vertex;

/**
 * Sets the robot destination to the provided location.
 *
 * @param[in] dest the vertex that identifies the destination.
 */
void set_robot_destination(struct Vertex dest);

/**
 * Updates the robot state for the preconfigured delta t.
 */
void update_robot_state(void);

/**
 * Gets the robot position.
 *
 * @return the current position of the robot.
 */
struct Vertex get_robot_position(void);

/**
 * Gets the robot heading.
 *
 * @return the current heading of the robot, in deg.
 */
double get_robot_heading(void);

/**
 * Returns the robot destination.
 *
 * @return the current destination of the robot.
 */
struct Vertex get_robot_destination(void);

#endif // ~ROBOT_H

