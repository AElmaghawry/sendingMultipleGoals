#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>

using namespace std;

// Action specification for move_base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{

    // Connect to ROS
    ros::init(argc, argv, "simple_navigation_goals");

    // tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait for the action server to come up so that we can begin processing goals.
    while (!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    int user_choice = 1;
    char choice_to_continue = 'Y';

    // Ask the user where he wants the robot to go?
    cout << "\n IF want to send the way-points for the Move-Base Goal Topic >>>>> press 'Y'?" << endl;

    cin >> choice_to_continue;
    // Create a new goal to send to move_base
    choice_to_continue = tolower(choice_to_continue);
    if (choice_to_continue = 'y')
    {
        bool run = true;

        while (run)
        {

            move_base_msgs::MoveBaseGoal goal;

            // Send a goal to the robot
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();

            bool valid_selection = true;

            // Use map_server to load the map of the environment on the /map topic.
            // Launch RViz and click the Publish Point button in RViz to
            // display the coordinates to the /clicked_point topic.
            switch (user_choice)
            {
            case 1:
                cout << "\nGoal Location: 1st Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = 13.8420;
                goal.target_pose.pose.position.y = 6.56259;
                goal.target_pose.pose.orientation.x = -0.006;
                goal.target_pose.pose.orientation.y = 0.0;
                goal.target_pose.pose.orientation.z = 1.0;
                goal.target_pose.pose.orientation.w = -0.008;
                break;
            case 2:
                cout << "\nGoal Location: 2nd Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = -0.684;
                goal.target_pose.pose.position.y = 6.5603;
                goal.target_pose.pose.orientation.x = -0.006;
                goal.target_pose.pose.orientation.y = 0.0;
                goal.target_pose.pose.orientation.z = 0.9996;
                goal.target_pose.pose.orientation.w = -0.0269;
                break;
            case 3:
                cout << "\nGoal Location: 3rd Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = -7.5910;
                goal.target_pose.pose.position.y = 3.994;
                goal.target_pose.pose.orientation.x = -0.0006;
                goal.target_pose.pose.orientation.y = -0.002;
                goal.target_pose.pose.orientation.z = 0.9620;
                goal.target_pose.pose.orientation.w = -0.0229;
                break;
            case 4:
                cout << "\nGoal Location: 4th Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = -12.03;
                goal.target_pose.pose.position.y = 3.994;
                goal.target_pose.pose.orientation.x = -0.0006;
                goal.target_pose.pose.orientation.y = -0.002;
                goal.target_pose.pose.orientation.z = 0.9719;
                goal.target_pose.pose.orientation.w = -0.2354;
                break;
            case 5:
                cout << "\nGoal Location: 5th Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = -15.56;
                goal.target_pose.pose.position.y = 0.968;
                goal.target_pose.pose.orientation.x = -0.0006;
                goal.target_pose.pose.orientation.y = -0.002;
                goal.target_pose.pose.orientation.z = 1.0;
                goal.target_pose.pose.orientation.w = 0.0;
                break;
            case 6:
                cout << "\nGoal Location: 6th Check point\n"
                     << endl;
                goal.target_pose.pose.position.x = -27.55;
                goal.target_pose.pose.position.y = 0.968;
                goal.target_pose.pose.orientation.x = -0.0006;
                goal.target_pose.pose.orientation.y = -0.002;
                goal.target_pose.pose.orientation.z = 1.0;
                goal.target_pose.pose.orientation.w = 0.0;
                break;
            default:
                cout << "\nInvalid selection. Please try again.\n"
                     << endl;
                valid_selection = false;
            }

            // Go back to beginning if the selection is invalid.
            if (!valid_selection)
            {
                continue;
            }

            ROS_INFO("Sending goal");
            ac.sendGoal(goal);

            // Wait until the robot reaches the goal
            ac.waitForResult();

            if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                ROS_INFO("The robot has arrived at the goal location");
                user_choice++;
            }

            else
            {
                ROS_INFO("The robot failed to reach the goal location for some reason");
                run = false;
            }

            // Ask the user if he wants to continue giving goals
        }
    }
    else
    {

        ROS_INFO("Enter a valid responce");
    }

    return 0;
}
