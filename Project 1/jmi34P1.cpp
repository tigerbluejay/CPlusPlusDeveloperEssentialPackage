/**
 *
 * jmi34P1.cpp
 *
 * COSC 051 Summer 2016
 * Project #1
 *
 * Due on: JUL 18, 2016
 * Author: Jose Maria Iriarte
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor recieved any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any coe taken from the class textebooks.
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*-----------------------------------------------------------------------
---------------------------- SET UP CONSTANTS ---------------------------
-----------------------------------------------------------------------*/

// constants

const double PI = 3.14;
const double COST_OF_RAW_MATERIALS = 4.79;
const double MARKUP = 0.26;
const int MIN_BASE_RADIUS = 4;
const int MAX_BASE_RADIUS = 20;
const int MIN_SHAPE_HEIGHT = 5;
const int MAX_SHAPE_HEIGHT = 25;
const int MIN_TOP_RADIUS = 0.0;

// string constants

const string WELCOME_MESSAGE = "Welcome to the Allegheny International Manufacturing's (AIM) ";
const string WELCOME_MESSAGE_2 = "Cone and Frustum Calculation Engine";
const string PROMPT_VALUE_SHAPE = "Please enter a shape code ( c – cone, f – frustum):";
const string PROMPT_VALUE_COLOR = "Please enter a color code (R, O, Y; G, B, I, V):";
const string PROMPT_VALUE_BASE_RADIUS = "Please enter the radius of the base ";
const string PROMPT_VALUE_BASE_RADIUS_2 = "( 4'' – 20'' ):";
const string PROMPT_VALUE_TOP_RADIUS = "Please enter the radius of the top ";
const string PROMPT_VALUE_SHAPE_HEIGHT = "Please enter the shape height ";
const string PROMPT_VALUE_IS_BASE_OPEN = "Should the base be open? (Y/N):";
const string PROMPT_VALUE_IS_TOP_OPEN = "Should the top be open? (Y/N):";

const string PROMPT_VALUE_SHAPE_ERROR = "The shape code entered is not a valid value. ";
const string PROMPT_VALUE_SHAPE_ERROR_2 = "Acceptable values are only (C)one and (F)rustum. ";
const string PROMPT_VALUE_SHAPE_ERROR_3 = "Program will now exit. Gooodbye...";
const string PROMPT_VALUE_COLOR_ERROR = "The color code entered is not a valid value. ";
const string PROMPT_VALUE_COLOR_ERROR_2 = "Acceptable values should be either (B)lue, (G)reen, ";
const string PROMPT_VALUE_COLOR_ERROR_3 = "(Y)ellow, (R)ed, (O)range, (I)ndigo, (V)iolet. ";
const string PROMPT_VALUE_COLOR_ERROR_4 = "Program will now exit. Gooodbye...";
const string PROMPT_VALUE_BASE_RADIUS_ERROR = "The radius of the base value entered ";
const string PROMPT_VALUE_BASE_RADIUS_ERROR_2 = "is not a valid value. Values must range ";
const string PROMPT_VALUE_BASE_RADIUS_ERROR_3 = "between 4 and 20 inches. Program will now ";
const string PROMPT_VALUE_BASE_RADIUS_ERROR_4 = "exit. Goodbye";
const string PROMPT_VALUE_TOP_RADIUS_ERROR = "The radius of the top value entered ";
const string PROMPT_VALUE_TOP_RADIUS_ERROR_2 = "is not a valid value. Values must range between ";
const string PROMPT_VALUE_TOP_RADIUS_ERROR_3 = "0.5 times the base radius and 0.75";
const string PROMPT_VALUE_TOP_RADIUS_ERROR_4 = "times the base radius. Program will now exit. ";
const string PROMPT_VALUE_TOP_RADIUS_ERROR_5 = "Gooodbye...";
const string PROMPT_VALUE_SHAPE_HEIGHT_ERROR = "The shape height value entered is ";
const string PROMPT_VALUE_SHAPE_HEIGHT_ERROR_2 = "not a valid value. Height must be at least ";
const string PROMPT_VALUE_SHAPE_HEIGHT_ERROR_3 = "five inches and at minimum equal to the ";
const string PROMPT_VALUE_SHAPE_HEIGHT_ERROR_4 = "base radius, and no more than 25 inches. ";
const string PROMPT_VALUE_SHAPE_HEIGHT_ERROR_5 = "Program will now exit. Gooodbye...";
const string PROMPT_VALUE_IS_BASE_OPEN_ERROR = "Please answer only typing Y or N ";
const string PROMPT_VALUE_IS_BASE_OPEN_ERROR_2 = "(yes or no) to indicate whether the base ";
const string PROMPT_VALUE_IS_BASE_OPEN_ERROR_3 = "should be open. Program will now exit. ";
const string PROMPT_VALUE_IS_BASE_OPEN_ERROR_4 = "Goodbye";
const string PROMPT_VALUE_IS_TOP_OPEN_ERROR = "Please answer only typing Y or N ";
const string PROMPT_VALUE_IS_TOP_OPEN_ERROR_2 = "(yes or no) to indicate whether the top should ";
const string PROMPT_VALUE_IS_TOP_OPEN_ERROR_3 = "be open. Program will now exit. Goodbye";

const string PROMPT_DATA_ENTERED = "Data Entered";
const string PROMPT_CALCULATED_VALUES = "Calculated Values";
const string PROMPT_MISC_FRUSTUM_DATA = "Additional Frusutum data";

const string THANK_YOU_MESSAGE = "Thank you for using AIM Software. We hope you ";
const string THANK_YOU_MESSAGE_2 = "enjoyed using our software.";

int main()
{
	/*-----------------------------------------------------------------------
	---------------------------- SET UP VARIABLES ---------------------------
	-----------------------------------------------------------------------*/

	char 	shapeType 				= '?';
	char 	colorCode 				= '?';
	double 	radiusTop 				= 0.0;
	double 	radiusBase 				= 0.0;
	double 	heightGF 				= 0.0;
	double	heightGC 				= 0.0;
	double 	height 					= 0.0;
	char 	baseOpen 				= '?';
	char 	topOpen 				= '?';
	double 	baseSurfaceArea 		= 0.0;
	double 	topSurfaceArea 			= 0.0;
	double 	lateralSurfaceArea 		= 0.0;
	double  totalSurfaceArea		= 0.0;
	double 	minBaseRadiusFrustum 	= 0.0;
	double 	maxBaseRadiusFrustum 	= 0.0;
	double 	theta 					= 0.0;
	double  totalCostOfRawMaterials = 0.0;
	double  salesPrice				= 0.0;

	/*-----------------------------------------------------------------------
	----RUN PROMPTS, REQUIRE INPUTS, CALCULATE WHAT IS REQUIRED--------------
	-----------------------------------------------------------------------*/

	cout << WELCOME_MESSAGE << WELCOME_MESSAGE_2 << endl;

	// is shape cone or frustum?
	
	cout << PROMPT_VALUE_SHAPE;
	cin >> shapeType;
	cout << endl;

	cin.ignore(500, '\n');


	if ( shapeType != 'C' && shapeType != 'c' && shapeType !='F' && shapeType != 'f')
	{
		cout << PROMPT_VALUE_SHAPE_ERROR << PROMPT_VALUE_SHAPE_ERROR_2 << 
		PROMPT_VALUE_SHAPE_ERROR_3 << endl;
		return 0;

	}

	// what color will the product be?
	
	cout << PROMPT_VALUE_COLOR;
	cin >> colorCode;
	cout << endl;

	cin.ignore(500, '\n');

	if ( colorCode != 'R' && colorCode != 'r' && colorCode != 'O' && colorCode !='o' 
		&& colorCode != 'Y' && colorCode !='y' && colorCode != 'G' && colorCode != 'g'
		&& colorCode != 'B' && colorCode != 'b' && colorCode != 'I' && colorCode != 'i'
		&& colorCode != 'V' && colorCode != 'v')
	{
		cout << PROMPT_VALUE_COLOR_ERROR << PROMPT_VALUE_COLOR_ERROR_2 <<
		PROMPT_VALUE_COLOR_ERROR_3 << PROMPT_VALUE_COLOR_ERROR_4 << endl;
		return 0;
	}

	// what will the base radius be?
	
	cout << PROMPT_VALUE_BASE_RADIUS << PROMPT_VALUE_BASE_RADIUS_2;
	cin >> radiusBase;
	cout << endl;

	if ( radiusBase < MIN_BASE_RADIUS || radiusBase > MAX_BASE_RADIUS)
	{
		cout << PROMPT_VALUE_BASE_RADIUS_ERROR << PROMPT_VALUE_BASE_RADIUS_ERROR_2
		<< PROMPT_VALUE_BASE_RADIUS_ERROR_3 << PROMPT_VALUE_BASE_RADIUS_ERROR_4 << endl;
		return 0;
	}

	// now that we know base radius we can calculate variables with min and max radii for
	// frustum we need to calculate them here as these will be used in later prompts to the
	// user and before general calculations
	
	minBaseRadiusFrustum = 0.5*radiusBase;
	maxBaseRadiusFrustum = 0.75*radiusBase;

	// if shape is frustum what will top radius be?
	
	if ( shapeType == 'F' || shapeType == 'f')
	{
		cout << PROMPT_VALUE_TOP_RADIUS << "( " << minBaseRadiusFrustum << "'' - " << 
		maxBaseRadiusFrustum 
		<< "'' ):";
		cin >> radiusTop;
		cout << endl;

		if ( radiusTop < minBaseRadiusFrustum || radiusTop > maxBaseRadiusFrustum)
		{
			cout << PROMPT_VALUE_TOP_RADIUS_ERROR << PROMPT_VALUE_TOP_RADIUS_ERROR_2 <<
			PROMPT_VALUE_TOP_RADIUS_ERROR_3 << PROMPT_VALUE_TOP_RADIUS_ERROR_4 <<
			PROMPT_VALUE_TOP_RADIUS_ERROR_5;
			return 0;
		}
	}

	// if shape is frustum what will height be?
	
	if ( shapeType == 'F' || shapeType == 'f')
	{
		cout << PROMPT_VALUE_SHAPE_HEIGHT << "(5'' – 25'' and at least " << 
		radiusBase << "'' ):";
		cin >> height;
		cout << endl;

		if ( height < MIN_SHAPE_HEIGHT || height > MAX_SHAPE_HEIGHT || height < 
			radiusBase) 
		{
			cout << PROMPT_VALUE_SHAPE_HEIGHT_ERROR << PROMPT_VALUE_SHAPE_HEIGHT_ERROR_2
			<< PROMPT_VALUE_SHAPE_HEIGHT_ERROR_3 << PROMPT_VALUE_SHAPE_HEIGHT_ERROR_4 <<
			PROMPT_VALUE_SHAPE_HEIGHT_ERROR_5;
			return 0;
		} else
		{
			heightGC = sqrt(pow((radiusTop * height) / (radiusBase - radiusTop), 2) +
			           pow(radiusTop, 2));
			heightGF = sqrt(pow((radiusTop * height) / (radiusBase - radiusTop), 2) + 
			           pow(radiusTop, 2)) + sqrt( pow(height, 2) + pow((radiusBase - 
			           radiusTop), 2));
		}

	// /*---------------arithmetic check -------------------
	//	cout << "HeightGC is : " << heightGC << endl;
	//	cout << "HeightGF is : " << heightGF << endl;
	// ----------------------------------------------------*/

	}

	// if shape is cone what will height be?
	
	if ( shapeType == 'C' || shapeType == 'c')
	{
		cout << PROMPT_VALUE_SHAPE_HEIGHT << "( MUST be 5 inches – 25 inches, and at least "
		<< radiusBase << " ):";
		cin >> height;
		cout << endl;

		if ( height < MIN_SHAPE_HEIGHT || height > MAX_SHAPE_HEIGHT || height < radiusBase)
		{
			cout << PROMPT_VALUE_SHAPE_HEIGHT_ERROR << PROMPT_VALUE_SHAPE_HEIGHT_ERROR_2
			<< PROMPT_VALUE_SHAPE_HEIGHT_ERROR_3 << PROMPT_VALUE_SHAPE_HEIGHT_ERROR_4 <<
			PROMPT_VALUE_SHAPE_HEIGHT_ERROR_5;
			return 0;
		} else 
		{
			heightGF = sqrt(pow((radiusTop * height) / (radiusBase - radiusTop), 2) +
			pow(radiusTop, 2)) + sqrt( pow(height, 2) + pow((radiusBase - radiusTop), 2));
		}
			
	}


	// if shape is frustum should the top be open?

	if ( shapeType == 'F' || shapeType == 'f')
	{
		cout << PROMPT_VALUE_IS_TOP_OPEN;
		cout << endl;
		cin >> topOpen;
		

		cin.ignore(500, '\n');

		if ( topOpen != 'Y' && topOpen != 'y' && topOpen != 'N' && topOpen != 'n')
		{
			cout << PROMPT_VALUE_IS_TOP_OPEN_ERROR << PROMPT_VALUE_IS_TOP_OPEN_ERROR_2 <<
			PROMPT_VALUE_IS_TOP_OPEN_ERROR_3;
			return 0;
		}
	}

	// for either frustum or cone will the base be open

	cout << PROMPT_VALUE_IS_BASE_OPEN << endl;
	cin >> baseOpen; 

	cin.ignore(500, '\n');

	if ( baseOpen != 'Y' && baseOpen != 'y' && baseOpen !='N' && baseOpen !='n')
	{
		cout << PROMPT_VALUE_IS_BASE_OPEN_ERROR << PROMPT_VALUE_IS_BASE_OPEN_ERROR_2 <<
		PROMPT_VALUE_IS_BASE_OPEN_ERROR_3 << PROMPT_VALUE_IS_BASE_OPEN_ERROR_4;
		return 0;
	} 


	/*-------------------------------------------------------(----------------
	--------------------------PERFORM GENERAL CALCULATIONS-------------------
	-----------------------------------------------------------------------*/
	
	baseSurfaceArea = PI*pow(radiusBase,2);
	
	if ( shapeType == 'F' || shapeType == 'f')
	{
		lateralSurfaceArea = PI*(radiusTop+radiusBase)*sqrt(pow(height,2)+pow((radiusBase 
		- radiusTop),2));

		if ( topOpen == 'N' || topOpen == 'n')
		{
			topSurfaceArea = PI*pow(radiusTop,2);
		} else
		{
			topSurfaceArea = 0;
		}

		if (baseOpen == 'N' || baseOpen == 'n')
		{
			baseSurfaceArea = PI*pow(radiusBase,2);		
		} else
		{
			baseSurfaceArea = 0;
		}
	} else  // if shape is not F and not any other letter or character (due to previous
	 		// validation, then it must be c or C)
	{
		lateralSurfaceArea = PI*radiusBase*sqrt(pow(radiusBase,2)+pow(height,2));
		topSurfaceArea = 0;

		if ( baseOpen == 'N' || baseOpen == 'n')
		{
			baseSurfaceArea = PI*pow(radiusBase,2);
		} else
		{
			baseSurfaceArea = 0;
		}
	}

	// perform general calculations that have not yet been performed
		
	totalSurfaceArea = lateralSurfaceArea + topSurfaceArea + baseSurfaceArea;
	totalCostOfRawMaterials = totalSurfaceArea*COST_OF_RAW_MATERIALS;
	salesPrice = totalCostOfRawMaterials + totalCostOfRawMaterials*MARKUP;
	theta = 180*((2*radiusBase - 2*radiusTop) / (heightGF - heightGC));

	/*-----------------------------------------------------------------------
	---------------OUTPUT DATA ENTERED AND CALCULATED VALUES-----------------
	-----------------------------------------------------------------------*/
	
	// output data entered by user
	
	cout << "\t" << PROMPT_DATA_ENTERED << endl;

	cout.width(20);
	cout << shapeType << " - shape code" << endl;
	cout.width(20);
	cout << colorCode << " - color code" << endl; 
	cout.width(20);
	cout << radiusBase << " - base radius" << endl;
	cout.width(20);
	cout << baseOpen << " - is base open" << endl;
	cout.width(20);
	cout << height << " - height specifed by user" << endl;
	
	if ( shapeType == 'F' || shapeType == 'f')
	{
		cout.width(20);
		cout << topOpen << " - is top open" << endl ;
		cout.width(20);
		cout << radiusTop << " - top radius" << endl << endl;
	}
	// output calculated values
	
	cout << endl;
	cout << "\t" << PROMPT_CALCULATED_VALUES << endl;
	
	cout << setprecision(5);
	cout.width(20);
	cout << right << baseSurfaceArea;
	cout << " - base surface area" << endl;
	cout.width(20);
	cout << lateralSurfaceArea << " - lateral surface area" << endl;
	cout.width(20);
	cout << topSurfaceArea << " - top surface area" << endl;
	cout.width(20);
	cout << totalSurfaceArea << " - total surface area" << endl;
	cout.width(20);
	cout << totalCostOfRawMaterials << " - total cost of raw materials" << endl;
	cout.width(20);
	cout << salesPrice << " - retail price" << endl;
	cout << endl;
	
	cout << THANK_YOU_MESSAGE << THANK_YOU_MESSAGE_2 << endl;

	return 0;
	
}