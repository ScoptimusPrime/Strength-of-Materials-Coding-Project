/*
 *
 * Scott Schneiderman
 * Strength of Materials Coding Project
 *
 */

using namespace std;
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
#include <string>

// Function Declaration
double mmToM (double mm);
double mTomm (double m);
double inToFt (double in);
double ftToIn (double ft);

int main() 
{
  /* 
   * Create variables
   * 'totalAngleOfTwist' used to store total angle of twist
   * 'totalSegment' used to define length of arrays
   * 'units' define metric or imperial
   */
  int totalSegments, units;
  double totalAngleOfTwist = 0;

    //prompts and holds number of rods
    cout << "Please enter the number of rods: "; 
    cin >> totalSegments;
    //checks input
    while (totalSegments < 1)                                                                                                  
    {
        cin.clear();
        cin.ignore(10000, '\n');

        //prompts and holds number of rods
        cout << "Invalid input, please enter a number greater than 0." << endl << "Please enter the number of rods: "; 
        cin >> totalSegments;
    }

  cout <<  "Please type in 0 for metric system or any other int for imperial.\n";
  cin >> units;

  // Create arrays which stores data for each segments length (L)
  double segmentLength[totalSegments];
  // Create arrays which stores data for each segments Outer Radius (D)
  double segmentOuterDiameter[totalSegments];
  // Create arrays which stores data for each segments Inner Radius (d)
  double segmentInnerDiameter[totalSegments];
  // Create arrays which stores data for each segments Torque (T)
  double segmentTorque[totalSegments];
  // Create arrays which stores data for each segments Modulus of Rigity (G)
  double segmentModulusOfRigidty[totalSegments];
  // Create arrays which stores data for each segments  angle of twist (theta)
  double segmentAngleOfTwist[totalSegments];
  // Create arrays which stores data for Torque applied to each segment (T in problem)
  double segmentGivenTorque[totalSegments];
  // Create arrays which stores data for Moment ofeach segments 
  double j[totalSegments];
  // Shear Sforce
  double segmentShearForce[totalSegments];

  // For Loop to determine individual legnth of each segment
  
  for(int i=0; i<totalSegments; i++)
  {
    cout << "Please enter the length of segment " << i+1 <<".(mm/in)\n";
    cin >> segmentLength[i];
    if (units == 0)
      segmentLength[i] = mmToM(segmentLength[i]);
    else
      segmentLength[i] = inToFt(segmentLength[i]);
  }

  // For Loop to determine individual modulus of rigity of each segment
  
  for(int i=0; i<totalSegments; i++)
  {
    cout << "Please enter the modulus of rigity for segment " <<i+1<< ", excluding the scientific notation.\n";
    cout << " Ex: 27*10^9, the input would be 27\n";
    double coeficient,exponent;
    cin >> coeficient;
    
    cout << "Please put in the exponential factor of the modulus of rigity.\n Ex: 27*10^9, the input would be 9.\n";
    cin >> exponent;
    segmentModulusOfRigidty[i] = coeficient*pow(10,exponent);
  }

  // For Loop to determine individual Outer Diameter of each segment
  for(int i=0; i<totalSegments; i++)
  {
    cout << "Please enter the Outer Diameter of segment " << i+1 <<" (mm/in)\n";
    cin >> segmentOuterDiameter[i];
    if (units == 0)
      segmentOuterDiameter[i] = mmToM(segmentOuterDiameter[i]);
    else
      segmentOuterDiameter[i] = inToFt(segmentOuterDiameter[i]);
  }

  // For Loop to determine individual Inner Diameter of each segment
  for(int i=0; i<totalSegments; i++)
  {
    cout << "Please enter the Inner Diameter of segment "<< i+1 <<"(mm/in)\n";
    cin >> segmentInnerDiameter[i];
    if (units == 0)
      segmentInnerDiameter[i] = mmToM(segmentInnerDiameter[i]);
    else
      segmentInnerDiameter[i] = inToFt(segmentInnerDiameter[i]);
  }

  // For Loop to determine individual Torque given of each segment
  for(int i=0; i<totalSegments; i++)
  {
    cout << "Please enter the Torque's magnitude (Nm) of segment " << i+1 << ".\n";
    cout << "If the force is counterclockwise, please input a positive integer. If clockwise, please put in as negative.\n";
    cin >> segmentGivenTorque[i];
  }

  // Calculate Torque in each segment
  for (int i = 0; i < totalSegments; i++)
  {
    segmentTorque[i] = 0;
  }
  
  for (int i = totalSegments-1; i >= 0; i--)
  {
    if (i == totalSegments-1)
    {
      segmentTorque[i] = -segmentGivenTorque[i];
    }
    else
    {
      segmentTorque[i] = -(-segmentTorque[i+1] + segmentGivenTorque[i]);
    }
  }

  //Print out array to ensure correct data
  for (int i = 0; i < totalSegments; i++)
  {
    cout << "torque at segment " << i+1 << ": " << segmentTorque[i] << "\n";
  }
  
  // Calculating Polar moment for each segment.
  for (int i = 0; i < totalSegments; i++)
  {
    // (pi/32)*(OuterDiameter^4 - InnerDiameter^4)
    j[i] = (M_PI/32)*((pow(segmentOuterDiameter[i],4))-(pow(segmentInnerDiameter[i],4)));
    cout << "polar moment of inertia for segment " << i + 1 << ": " << j[i] << "\n";
  }

  // Calculating Shear Stress Calculated Here */
  for (int i = 0; i < totalSegments; i++)
  {
    segmentShearForce[i] = (segmentTorque[i]*((segmentOuterDiameter[i]-segmentInnerDiameter[i])/2))/j[i];
    cout << "Max shear stress in segment " << i+1 <<": " << segmentShearForce[i] << "\n";
  }

  // Calculating individual section theta
  for (int i = 0; i < totalSegments; i++)
  {
    // (Tau*L)/(J*G)
    segmentAngleOfTwist[i] = ((segmentTorque[i]*segmentLength[i])/(j[i]*segmentModulusOfRigidty[i]));
    cout << "The angle of twist in section " << i+1 <<" is: " << segmentAngleOfTwist[i] << "\n";
  }

  // Calculating total angle of twist
  for (int i = 0; i < totalSegments; i++)
  {
    totalAngleOfTwist += segmentAngleOfTwist[i];
    cout << "yeet " << segmentAngleOfTwist[i] << "\n";
  }
  cout << "The total angle of twist is: ";
  cout << totalAngleOfTwist;
  return 0; 
}

//Convert milimeters to meters
double mmToM (double mm)
{
  double m = mm/1000;
  return m;
}
// Convert meters to milimeters (may be extraneous)
double mTomm (double m)
{
  double mm = m*1000;
  return mm;
}
// Convert inches to feet
double inToFt (double in)
{
  double ft = in/12;
  return ft;
}
// Convert feet to inches (may be extraneous)
double ftToIn (double ft)
{
  double in = ft*12;
  return in;
}