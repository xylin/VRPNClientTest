// VRPNKinectConsole.cpp : Defines the entry point for the console application.
//

 #include "stdafx.h"
 #include <cstdlib>
 #include <vrpn_Tracker.h>
 #include <quat.h>
#include <iostream>
static void VRPN_CALLBACK tracker_handler(void *userdata, const vrpn_TRACKERCB t);

// Position and orientation of each joint
static double position[2][3];
static double orientation[2][4];

int _tmain(int argc, _TCHAR* argv[])
{
        // Create a remote to track output
        vrpn_Tracker_Remote *remote = new vrpn_Tracker_Remote("Tracker0@localhost");
        remote->register_change_handler(NULL, tracker_handler);
        remote->shutup = true;

        double eulerOrientation[3];

        // Endless loop to print the changing values
        while (true)
        {
                // Update the joint positions
                remote->mainloop();

                // Clear console
                system("cls");

                for (int i=0; i<2; i++)
                {
                        // Convert orientation quaternion to euler angles
                        q_to_euler(eulerOrientation, orientation[i]);

                        // Output updated data
                        printf("\nJoint: %i", i);
                        printf("Position:\nX: %d\nY: %d\nZ: %d", position[i][0], position[i][1], position[i][2]);
                        printf("Orientation:\nYaw: %d\nPitch: %d\nRoll: %d", eulerOrientation[0], eulerOrientation[1], eulerOrientation[2]);
                }

				//std::cout << std::endl << std::endl;

				_sleep(500);
        }

        return 0;
}

static void VRPN_CALLBACK tracker_handler(void *userdata, const vrpn_TRACKERCB t)
{
        // Store the updated position and orientation of the targeted joint
        q_vec_copy(position[t.sensor], t.pos);
        q_copy(orientation[t.sensor], t.quat);

//	std::cout << "Tracker '" << t.sensor << "' : " << t.pos[0] << "," <<  t.pos[1] << "," << t.pos[2] << std::endl;
}

