
/**
 *
 * jmi34P3.cpp
 *
 * COSC 051 Summer 2016
 * Project #3
 *
 * Due on: AUG 2, 2016
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
 * or any code taken from the class textebooks.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <locale>
#include <vector>

using namespace std;

/* --------------------------------------------
--- DECLARE CONSTANTS - NO MAGIC NUMBERS ------
----------------------------------------------*/

const double PI = 3.14;
const double COST_OF_RAW_MATERIALS = 4.79;
const double MARKUP = 0.26;
const int MIN_BASE_RADIUS = 4;
const int MAX_BASE_RADIUS = 20;
const int MIN_SHAPE_HEIGHT = 5;
const int MAX_SHAPE_HEIGHT = 25;
const int MIN_TOP_RADIUS = 0.0;
const int THETA_MULTIPLE = 180;

const string WELCOME_MESSAGE = "Welcome to the Allegheny International Manufacturing's (AIM).\n";
const string WELCOME_MESSAGE_2 = "Cone and Frustum Fabrication Division.\n";
const string WELCOME_MESSAGE_3 = "This application calculates pattern measurements,\n";
const string WELCOME_MESSAGE_4 = "surface area, cost and price for frustum and cone shapes.\n";

const string MENU_PROMPT = "Please select the letter corresponding to your choice\n";

const string OPEN_FILE_PROMPT = "Please enter the name of the input data file to load:\n";
const string OPEN_FILE_ERROR = "ERROR reading file. Program will terminate now...\n";
const string OPEN_FILE_ERROR_2 = "file was either empty of there was an issue attempting to load ";
const string OPEN_FILE_ERROR_3 = "the contents, no records were added to vectors\n";
const string OPEN_FILE_SUCCESS = "file contents loaded successfully!\n";

const string SHAPE_ERROR = "\n\t The shape code entered is not a valid value";
const string COLOR_ERROR = "\n\t The color code entered is not a valid value";
const string BASE_RADIUS_ERROR = "\n\t The base radius entered is outside the limits";
const string TOP_RADIUS_ERROR = "\n\t The top radius entered is outside the limits";
const string HEIGHT_ERROR = "\n\t The height value entered is not valid";
const string BASE_CLOSED_ERROR = "\n\t The base closed entered selection is not a valid value";
const string TOP_CLOSED_ERROR = "\n\t The top closed entered selection is not a valid value";

const string TOTAL_RECORDS = " total records\n";
const string RECORDS_WITH_ONE_INVALID_VALUE = " records containing at least one invalid value\n";
const string CONE_RECORDS_NO_ERRORS = " cone records with NO errors\n";
const string FRUSTUM_RECORDS_NO_ERRORS =  " frustum records with NO errors\n";

const string LOAD_FILE_PROMPT = "Please load data prior to displaying reports\n";
const string VALID_OPTIONS_PRE_PROMPT = " is not a valid choice.\n";
const string VALID_OPTIONS_PROMPT = "Check the menu options and try again\n";

const string LOAD_FILE = "\t\tL - Load file\n";
const string REGION_SUMMARY_REPORT = "\t\tR - Region Summary Report\n";
const string SHAPE_SUMMARY_REPORT = "\t\tS - Shape Summary Report\n";
const string QUIT_PROMPT = "\t\tQ - Quit\n";


const string THANK_YOU_MESSAGE = "Thank you for using Alleghany International\n";
const string THANK_YOU_MESSAGE_2 = "Manufacturing (AIM) software.\n";

// constants to use for column width and other table formatting

const int W_H1 = 45;

// widths for file record outputs
const int W_C2 = 5;
const int W_C3 = 22;
const int W_C4 = 8;
const int W_C5 = 18;
const int W_C6 = 6;
const int W_C7 = 19;

// widths for results tables
const int W_R1 = 6;
const int W_R2 = 18;
const int W_R3 = 22;
const int W_R4 = 5;
const int W_R5 = 23;
const int W_R6 = 20;

// long widths
const int L1 = 76;
const int L2 = 90;

/*-------------------------------------------------------------------
-----------------------FUNCTION PROTOTYPES -------------------------
--------------------------------------------------------------------*/

char showMenu ();

bool loadData( string fileName, vector<string> &vRegion, vector<char> &vShapeCode,
    vector<char> &vColorCode, vector<double> &vRadius2, vector<double> &vRadius1,
    vector<double> &vHeight2, vector<char> &vClosedBase, vector<char> &vClosedTop);


double getGC( double r2, double r1, double h2);

double getGF( double r2, double r1, double h2);

double getTheta( double r2, double r1, double h2);


double getTotalSurfaceArea( double r2, double r1, double h2, char sCode,
    char closedBase, char closedTop);

void summaryByRegion( const vector<string> &reg, const vector<char> &sC,
    const vector<char> &cC, const vector<double> &r2,
    const vector<double> &r1, const vector<double> &h2,
    const vector<char> &cBase, const vector<char> &cTop);

void summaryByShape( const vector<string> &reg, const vector<char> &sC,
    const vector<char> &cC, const vector<double> &r2,
    const vector<double> &r1, const vector<double> &h2,
    const vector<char> &cBase, const vector<char> &cTop);





int main(int argc, const char * argv[])
{
    string fileName = "";
    ifstream inFile;

    
    /* --------------------------------------------
    --------- DECLARE LOCAL VARIABLES - -----------
    ----------------------------------------------*/


    vector<string> vRegion;
    vector<char> vShapeCode;
    vector<char> vColorCode;
    vector<double> vRadius2;
    vector<double> vRadius1;
    vector<double> vHeight2;
    vector<char> vClosedBase;
    vector<char> vClosedTop;


    bool loadWasSuccessful = false;

    char userSelection = '?'; // stores what is returned from the call from showMenu
    

    /*-------------------------------------------------------------------------
    ----------------------------- MENU EXECUTION ------------------------------
    -------------------------------------------------------------------------*/    

    cout << WELCOME_MESSAGE << WELCOME_MESSAGE_2 << WELCOME_MESSAGE_3
    << WELCOME_MESSAGE_4 << endl;

    while ( userSelection != 'Q' && userSelection != 'q')
    {

        userSelection = showMenu();  // presents the menu and stores in the user option.

        switch (userSelection) // this whole switch needs to go inside a while.
        {
            case 'L':
            case 'l':
                    
                    cout << OPEN_FILE_PROMPT << endl;
                    cin >> fileName;

                    loadWasSuccessful = loadData(fileName, vRegion, vShapeCode, vColorCode,
                                        vRadius2, vRadius1, vHeight2, vClosedBase, vClosedTop);

                    break;

            case 'R':
            case 'r':

                    if (loadWasSuccessful == false) 
                    {
                        cout << endl;
                        cout << LOAD_FILE_PROMPT;
                        cout << endl;
                        break;
                    } else 
                    {

                    summaryByRegion(vRegion, vShapeCode, vColorCode, vRadius2, vRadius1,
                                    vHeight2, vClosedBase, vClosedTop);

                    break;

                    }

            case 'S':
            case 's':

                    if (loadWasSuccessful == false) 
                    {
                        cout << endl;
                        cout << LOAD_FILE_PROMPT;
                        cout << endl;
                        break;
                    } else 
                    {
 
                    summaryByShape(vRegion, vShapeCode, vColorCode, vRadius2, vRadius1, vHeight2,
                     vClosedBase, vClosedTop);
 
                    break;
                    }

            case 'Q':
            case 'q':

                    break;

            default:
                    cout << "'" << userSelection << "'" << "is not a valid choice.\n" << VALID_OPTIONS_PROMPT;
                    cout << endl;
        } // end switch

    } // end while
    
    cout << THANK_YOU_MESSAGE << THANK_YOU_MESSAGE_2 << endl;

    return 0;
} //END function main()


char showMenu()
{
    
    char userOption = '?';
    
    cout << endl;
    cout << MENU_PROMPT;
    cout << endl;
    cout << LOAD_FILE;
    cout << REGION_SUMMARY_REPORT;
    cout << SHAPE_SUMMARY_REPORT;
    cout << QUIT_PROMPT;
    cout << endl;

    cin >> userOption;
    
    return userOption;
    
} //END function showMenu()


bool loadData( string fileName, vector<string> &vRegion, vector<char> &vShapeCode,
        vector<char> &vColorCode, vector<double> &vRadius2, vector<double> &vRadius1,
        vector<double> &vHeight2, vector<char> &vClosedBase, vector<char> &vClosedTop)
{

    double  minBaseRadiusFrustum    = 0.0;
    double  maxBaseRadiusFrustum    = 0.0;

    double  heightGF                = 0.0;
    double  heightGC                = 0.0;
    double  angleTheta              = 0.0;

    string  oneLine = "";

    // Extracted (Ext suffixed) variables
    
    int oYear = 0;
    int oMonth = 0;
    int oDay = 0;
    char chExt = '?';
    int dYear = 0;
    int dMonth = 0;
    int dDay = 0;
    char shapeCodeExt = '?';
    char colorCodeExt = '?';
    double radiusBaseExt = 0.0;
    double radiusTopExt = 0.0;
    double heightExt = 0.0;
    char closedTopExt = '?';
    char closedBaseExt = '?';
    string orderNumberExt = "";
    string stateCodeExt = "";
    string regionExt = "";
    string shipToExt = "";

    // error flags and message variables
    
    bool atLeastOneErrorFlag1 = false;
    bool atLeastOneErrorFlag2 = false; // color error
    bool atLeastOneErrorFlag3 = false; // base radius error
    bool atLeastOneErrorFlag4 = false; // top radius error
    bool atLeastOneErrorFlag5 = false; // height error
    bool atLeastOneErrorFlag6 = false; // base open or closed error
    bool atLeastOneErrorFlag7 = false; // top open or closed
    bool coneRecordWithNoError2 = false; // color error
    bool frustumRecordWithNoError2 = false; // color error
    bool coneRecordWithNoError3 = false; // base radius error
    bool frustumRecordWithNoError3 = false; // base radius error
    bool frustumRecordWithNoError4 = false; // top radius error
    bool coneRecordWithNoError5 = false; // height error
    bool frustumRecordWithNoError5 = false; // height error
    bool coneRecordWithNoError6 = false; // base open or closed error
    bool frustumRecordWithNoError6 = false; // base open or closed error
    bool frustumRecordWithNoError7 = false; // top open or closed error

    string shapeErrorMessage = "";
    string colorErrorMessage = "";
    string baseRadiusErrorMessage = "";
    string topRadiusErrorMessage = "";
    string heightErrorMessage = "";
    string baseClosedErrorMessage = "";
    string topClosedErrorMessage = "";

    // toupper chars
    char shapeCodeToUpper = '?';
    char colorCodeToUpper = '?';
    char baseClosedToUpper = '?';
    char topClosedToUpper = '?';

    // counters    
    int coneRecordCounter = 0;
    int frustumRecordCounter = 0;
    int totalRecordCounter = 0;
    int atLeastOneErrorCounter = 0;
    
    bool loadWasSuccessful = false;

    char userSelection = '?'; // stores what is returned from the call from showMenu

    double gCValue = 0.0;
    double gFValue = 0.0;
    double thetaValue = 0.0;

    ifstream inFile;

    inFile.open(fileName.c_str());

    if (!inFile)
    {
        cout << endl;
        cout << OPEN_FILE_ERROR << " " << fileName << " " << OPEN_FILE_ERROR_2 << OPEN_FILE_ERROR_3;
        cout << endl;
    } 
    else
    {
 

    /* ----------------------------------------
    ------------ TABLE FOR OUTPUT  -----------
    -----------------------------------------*/

    cout << endl << endl;

    cout << setfill('-') << setw(L2) << "-" <<  endl; 
    cout << setfill(' ');

    cout << setw(W_H1) << "Shape Orders" << endl;

    cout << setfill('-') << setw(L2) << "-" <<  endl; 
    cout << setfill(' ');


    cout << left << setw(W_C4) << "Shape" << setw(W_C4) << "Color" << setw(W_C4) << "" 
    << setw(W_C4) << "" << setw(W_C4) << "" << setw(W_C4) << right << "Base" 
    << setw(W_C4) << "Top" << setw(W_C4) << right << "line" << setw(W_C4) << "line" 
    << setw(W_C4) << "angle" << endl;   
    cout << left << setw(W_C4) << "Code" << setw(W_C4) << "Code" << setw(W_C4) << "r2" 
    << setw(W_C4) << "r1" << setw(W_C4) << "h2" << setw(W_C4) << right << "Closed" 
    << setw(W_C4) << "Closed" << setw(W_C4) << right << "CG" << setw(W_C4) << "GF" 
    << setw(W_C4) << "theta" << endl;   


    cout << setfill('-') << setw(L2) << "-" <<  endl; 
    cout << setfill(' ');


    // -------------- READ ADMIN INFO --------

    getline(inFile, oneLine); // read the admin information

    cout << oneLine << endl;   

        while ( inFile >> oYear >> chExt >> oMonth >> chExt >> oDay >> dYear >> chExt >> dMonth &&
        inFile >> chExt >> dDay >> orderNumberExt >> stateCodeExt >> regionExt &&
        inFile >> shapeCodeExt >> colorCodeExt >> radiusBaseExt >> radiusTopExt &&
        inFile >> heightExt >> closedBaseExt >> closedTopExt && getline(inFile, shipToExt))
        {

           /* ----------------- SET SHAPE ---------------*/
            
            if ( shapeCodeExt != 'C' && shapeCodeExt != 'c' && shapeCodeExt !='F' && 
                shapeCodeExt != 'f')
            {
                shapeErrorMessage = SHAPE_ERROR;
                atLeastOneErrorFlag1 = true;
                

            } else if ( shapeCodeExt == 'C' || shapeCodeExt == 'c') 
            {
                shapeErrorMessage = "";
                atLeastOneErrorFlag1 = false;

            } else
            {
                shapeErrorMessage = "";
                atLeastOneErrorFlag1 = false;
                

            } // end if ( shapeCodeExt ...

            /*--------------------- SET COLOR -------------------*/

            if ( colorCodeExt != 'R' && colorCodeExt != 'r' && colorCodeExt != 'O' 
                && colorCodeExt !='o' && colorCodeExt != 'Y' && colorCodeExt !='y' 
                && colorCodeExt != 'G' && colorCodeExt != 'g' && colorCodeExt != 'B' 
                && colorCodeExt != 'b' && colorCodeExt != 'I' && colorCodeExt != 'i' 
                && colorCodeExt != 'V' && colorCodeExt != 'v')
            {
                
                colorErrorMessage = COLOR_ERROR;
                atLeastOneErrorFlag2 = true;
                coneRecordWithNoError2 = false;
                frustumRecordWithNoError2 = false;
            
            } else 
            {

            colorErrorMessage = "";
            atLeastOneErrorFlag2 = false;
            coneRecordWithNoError2 = false;
            frustumRecordWithNoError2 = false;

                if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
                {
                    coneRecordWithNoError2 = true;
                    


                } else if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
            
                {
                    frustumRecordWithNoError2 = true;

                }


            } // end if

            /*------------------ SET BASE RADIUS -------------------*/
            
            if ( radiusBaseExt < MIN_BASE_RADIUS || radiusBaseExt > MAX_BASE_RADIUS)
            {    
                baseRadiusErrorMessage = BASE_RADIUS_ERROR;
                atLeastOneErrorFlag3 = true;
                coneRecordWithNoError3 = false;
                frustumRecordWithNoError3 = false;
            
            } else

            {
                
                baseRadiusErrorMessage = "";
                atLeastOneErrorFlag3 = false;
                coneRecordWithNoError3 = false;
                frustumRecordWithNoError3 = false;

                if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
                {
                    coneRecordWithNoError3 = true;
                    


                } else if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
                {
                    frustumRecordWithNoError3 = true;
                    
                }

                minBaseRadiusFrustum = 0.5*radiusBaseExt;
                maxBaseRadiusFrustum = 0.75*radiusBaseExt;

            } // end if
        
            /*-------------------SET TOP RADIUS  -------------------*/
        
            if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
            {

                topRadiusErrorMessage = "";
                atLeastOneErrorFlag4 = false;
                frustumRecordWithNoError4 = false;

                if ( radiusTopExt < minBaseRadiusFrustum || radiusTopExt > maxBaseRadiusFrustum )
                {
                
                    topRadiusErrorMessage = TOP_RADIUS_ERROR;
                    atLeastOneErrorFlag4 = true;
                    frustumRecordWithNoError4 = false;
                    
                } else // frustum record is within allowable parameters
                {
                    frustumRecordWithNoError4 = true;
                    atLeastOneErrorFlag4 = false;
                    
                    
                }
            
            } else 
            {
                topRadiusErrorMessage = "";
                atLeastOneErrorFlag4 = false;
                
                
            } // end if

            /*-------------------SET HEIGHT ------------------------*/

            if ( heightExt < MIN_SHAPE_HEIGHT || heightExt > MAX_SHAPE_HEIGHT || heightExt < 
                radiusBaseExt ) 
            {
                heightErrorMessage = HEIGHT_ERROR;
                atLeastOneErrorFlag5 = true;
                coneRecordWithNoError5 = false;
                frustumRecordWithNoError5 = false;

            } else 
            {

                heightErrorMessage = "";
                atLeastOneErrorFlag5 = false;
                coneRecordWithNoError5 = false;
                frustumRecordWithNoError5 = false;

                if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
                {
                    coneRecordWithNoError5 = true;
                    

                } else if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
                {
                    frustumRecordWithNoError5 = true;
                }


            } // end if

            /*-------------------SET BASE CLOSED -------------------*/

            if ( closedBaseExt != 'Y' && closedBaseExt != 'y' && closedBaseExt !='N' 
                && closedBaseExt !='n')
            {
                
                baseClosedErrorMessage = BASE_CLOSED_ERROR;
                atLeastOneErrorFlag6 = true;
                coneRecordWithNoError6 = false;
                frustumRecordWithNoError6 = false;

            
            } else 
            {

                baseClosedErrorMessage = "";
                atLeastOneErrorFlag6 = false;
                coneRecordWithNoError6 = false;
                frustumRecordWithNoError6 = false;

                if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
                {
                    coneRecordWithNoError6 = true;

                } else if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
                {
                    frustumRecordWithNoError6 = true;
                }

            } // end if


            /*-------------------SET TOP CLOSED -------------------*/
        

            if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
            {

                topClosedErrorMessage = "";
                atLeastOneErrorFlag7 = false;
                frustumRecordWithNoError7 = false;

                if ( closedTopExt != 'Y' && closedTopExt != 'y' && closedTopExt !='N' 
                    && closedTopExt !='n')
                {
                
                    topClosedErrorMessage = TOP_RADIUS_ERROR;
                    atLeastOneErrorFlag7 = true;
                    frustumRecordWithNoError7 = false;
                    
                } else // frustum record is within allowable parameters
                {
                    frustumRecordWithNoError7 = true;
                    atLeastOneErrorFlag7 = false;
                    
                }
            
            } else 
            {
                topClosedErrorMessage = "";
                atLeastOneErrorFlag7 = false;
                
                
            } // end if

            /*----------------CALCULATE GC, GF, and theta----------------*/
            if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
                || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
                || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
                || atLeastOneErrorFlag7 == true)  
            {

                heightGF = 0;
                heightGC = 0;
                angleTheta = 0;

            } else
            {      

                int rad2 = radiusBaseExt;
                int rad1 = radiusTopExt;
                int hei2 = heightExt;

                gFValue = getGF(rad2, rad1, hei2);
                gCValue = getGC(rad2, rad1, hei2);
                thetaValue = getTheta(rad2, rad1, hei2);

            } // end if

            /*------------------- REPORT COUNTERS -----------------------*/

            if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
                || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
                || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
                || atLeastOneErrorFlag7 == true)  
            {
                atLeastOneErrorCounter++;
            } else {

                vRegion.push_back(regionExt);
                vShapeCode.push_back(shapeCodeExt);
                vColorCode.push_back(colorCodeExt);
                vRadius2.push_back(radiusBaseExt);
                vRadius1.push_back(radiusTopExt);
                vHeight2.push_back(heightExt);
                vClosedBase.push_back(closedBaseExt);
                vClosedTop.push_back(closedTopExt);

            } // end if

            if (coneRecordWithNoError2 == true && coneRecordWithNoError3 == true 
                && coneRecordWithNoError5 == true && coneRecordWithNoError6 == true)
            {
                coneRecordCounter++;
                coneRecordWithNoError2 = false;
                coneRecordWithNoError3 = false;
                coneRecordWithNoError5 = false;
                coneRecordWithNoError6 = false;

            } // end if

            if (frustumRecordWithNoError2 == true && frustumRecordWithNoError3 == true 
                && frustumRecordWithNoError4 == true && frustumRecordWithNoError5 == true 
                && frustumRecordWithNoError6 == true && frustumRecordWithNoError7 == true)
            {
                frustumRecordCounter++;
                frustumRecordWithNoError2 = false;
                frustumRecordWithNoError3 = false;
                frustumRecordWithNoError4 = false;
                frustumRecordWithNoError5 = false;
                frustumRecordWithNoError6 = false;
                frustumRecordWithNoError7 = false;
            } // end if 

            totalRecordCounter++;

            shapeCodeToUpper = toupper(shapeCodeExt);
            colorCodeToUpper = toupper(colorCodeExt);
            baseClosedToUpper = toupper(closedBaseExt);
            topClosedToUpper = toupper(closedTopExt);

                
            if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
                || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
                || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
                || atLeastOneErrorFlag7 == true)  
            {
            
                if ( radiusTopExt == 0)
                {
                
                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                    << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt << setw(W_C4) << "n/a" << setw(W_C4) 
                    << heightExt << setw(W_C4) << right << baseClosedToUpper 
                    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << "" << setw(W_C4) << "" << setw(W_C4) << setprecision(3) << "";   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;

                    cout << endl;

                } else
                
                {
                
                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) << 
                    colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt << setw(W_C4) << radiusTopExt << setw(W_C4) 
                    << heightExt << setw(W_C4) << right << baseClosedToUpper
                    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << "" << setw(W_C4) << "" << setw(W_C4) << setprecision(3) << "";   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;
                    
                    cout << endl;

                }
        

            } else {

                if ( heightGC == 0 && radiusTopExt != 0)
                {
                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) << 
                    colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt << setw(W_C4) << radiusTopExt << setw(W_C4) 
                    << heightExt << setw(W_C4) << right << baseClosedToUpper
                    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << "n/a" << setw(W_C4) << gFValue << setw(W_C4) << setprecision(3) 
                    << thetaValue;   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;

                } else if ( heightGC != 0 && radiusTopExt == 0)

                {

                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                    << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt << setw(W_C4) << "n/a" << setw(W_C4) 
                    << heightExt << setw(W_C4) << right << baseClosedToUpper
                    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << gCValue << setw(W_C4) << gFValue << setw(W_C4) 
                    << setprecision(3) << thetaValue;   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;


                } else if ( heightGC == 0 && radiusTopExt == 0)

                {

                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                    << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt << setw(W_C4) << "n/a" << setw(W_C4) 
                    << heightExt << setw(W_C4) << right << baseClosedToUpper << setw(W_C4) 
                    << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << "n/a" << setw(W_C4) << gFValue << setw(W_C4) 
                    << setprecision(3) << thetaValue;   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;


                } else 

                {
                  
                    cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                    << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                    << right << radiusBaseExt  << setw(W_C4) << radiusTopExt 
                    << setw(W_C4) << heightExt << setw(W_C4) << right << baseClosedToUpper 
                    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                    << fixed << gCValue << setw(W_C4) << gFValue << setw(W_C4) 
                    << setprecision(3) << thetaValue;   
                    cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                    << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                    << topClosedErrorMessage << endl;

                }


            } // end if

        } // end while 

    cout << endl;
    cout << setw(W_C4) << right << totalRecordCounter << setw(W_C4) << left << TOTAL_RECORDS;
    cout << setw(W_C4) << right << atLeastOneErrorCounter << setw(W_C4+W_C4+W_C4) << left 
    << RECORDS_WITH_ONE_INVALID_VALUE;
    cout << setw(W_C4) << right << coneRecordCounter << setw(W_C4+W_C4+W_C4) << left 
    << CONE_RECORDS_NO_ERRORS;
    cout << setw(W_C4) << right << frustumRecordCounter << setw(W_C4+W_C4+W_C4) << left 
    << FRUSTUM_RECORDS_NO_ERRORS;
    cout << endl;

    cout << fileName << endl;
    cout << OPEN_FILE_SUCCESS;
    cout << endl;

    return loadWasSuccessful = true;

    } // end if

} // end loadData();


double getGF( double r2, double r1, double h2) 
{
    
    double heightGF = 0;

    heightGF = sqrt(pow((r1 * h2) / (r2 - r1), 2) + pow(r1, 2)) + sqrt( pow(h2, 2) 
               + pow((r2 - r1), 2));                   
    
    return heightGF;

} // end getGF()


double getGC( double r2, double r1, double h2)
{

    
    double heightGC = 0;
    
    heightGC = sqrt(pow((r1 * h2) / (r2 - r1), 2) + pow(r1, 2));

    return heightGC;

} // end getGC()


/****************************************************************************
 **                                                                        **
 **                          function getTheta                             **
 **                                                                        **
 **               Function getTheta is provided to                         **
 **               students in COSC 051 Summer 2016                         **
 **               to use in part or in total for class                     **
 **               projects.  Students may use this code                    **
 **               as their own, without any attribution.                   **
 **                                                                        **
 ****************************************************************************/

double getTheta( double r2, double r1, double h2)
{
    // These are intermediate variables that I used in my Project #2
    // cout << "Entered function getTheta()\n";

    double p1 = 0.0, p2 = 0.0;
    
    // I copied the values passed to the function parameters into 
    // additional local variables that matched the variable identifiers
    // used in my Project #2 code you may follow this strategy
    // or you may simply change the identifiers in this function
    // heading to match your Project #2 identifiers
    
    double radius2 = r2, radius1 = r1, height2 = h2;
    
    double angleTheta = 0.0;
        
    //calculate angleTheta in several steps
    p1 = ( (2 * radius2) - (2 * radius1) );
    
    // NOTE: This function makes calls to getGF and getGC, you will 
    //       need to implement both of those other functions before
    //       function getTheta will return accurate values
    
    p2 = getGF(r2,r1,h2) - getGC(r2,r1,h2);
    
    angleTheta = 180 * (p1 / p2);    

    // cout << "Exiting function getTheta()\n";

    return angleTheta;
    
} // end getTheta()


double getTotalSurfaceArea( double r2, double r1, double h2, char sCode,
        char closedBase, char closedTop)
{

    double lateralSurfaceArea = 0.0;
    double topSurfaceArea = 0.0;
    double baseSurfaceArea = 0.0;
    double totalSurfaceArea = 0.0;


    if ( sCode == 'F' || sCode == 'f')
        {
        lateralSurfaceArea = PI*(r1+r2)*sqrt(pow(h2,2)+pow((r2 - r1),2));

        if ( closedTop == 'Y' || closedTop == 'y')
        {
            topSurfaceArea = PI*pow(r1,2);
        } else
        {
            topSurfaceArea = 0;
        }

        if ( closedBase == 'Y' || closedBase == 'y')
        {
            baseSurfaceArea = PI*pow(r2,2);     
        } else
        {
            baseSurfaceArea = 0;
        }
    
    } else if ( sCode == 'C' || sCode == 'c')
    {
        lateralSurfaceArea = PI*r2*sqrt(pow(r2,2)+pow(h2,2));
        topSurfaceArea = 0;

        if ( closedBase == 'Y' || closedBase == 'y')
        {
            baseSurfaceArea = PI*pow(r2,2);
        } else
        {
            baseSurfaceArea = 0;
        }
    } // end if

    return totalSurfaceArea = lateralSurfaceArea + topSurfaceArea + baseSurfaceArea;

} // end getTotalSurfaceArea()

void summaryByRegion( const vector<string> &vRegion, const vector<char> &vShapeCode,
        const vector<char> &vColorCode, const vector<double> &vRadius2,
        const vector<double> &vRadius1, const vector<double> &vHeight2,
        const vector<char> &vClosedBase, const vector<char> &vClosedTop)
{
    
    // define variables
    // initialize variables, all the counters and running totals

    double rad2 = 0.0;
    double rad1 = 0.0;
    double hei2 = 0.0;
    char sCode = '?';
    char closedBase = '?';
    char closedTop = '?';
    double totalSurfaceArea = '?';

    double totalCostOfRawMaterialsN = 0.0;
    double totalCostOfRawMaterialsS = 0.0;
    double totalCostOfRawMaterialsE = 0.0;
    double totalCostOfRawMaterialsW = 0.0;
    double totalCostOfRawMaterialsO = 0.0;

    double salesPriceN = 0.0;
    double salesPriceS = 0.0;
    double salesPriceE = 0.0;
    double salesPriceW = 0.0;
    double salesPriceO = 0.0;

    double SumOfTotalSurfaceAreasN = 0.0;
    double SumOfTotalSurfaceAreasE = 0.0;
    double SumOfTotalSurfaceAreasW = 0.0;
    double SumOfTotalSurfaceAreasS = 0.0;
    double SumOfTotalSurfaceAreasO = 0.0;

    double SumOfTotalCostOfRawMaterialsN = 0.0;
    double SumOfTotalCostOfRawMaterialsE = 0.0;
    double SumOfTotalCostOfRawMaterialsW = 0.0;
    double SumOfTotalCostOfRawMaterialsS = 0.0;
    double SumOfTotalCostOfRawMaterialsO = 0.0;

    double SumOfTotalSalesPricesN = 0.0;
    double SumOfTotalSalesPricesW = 0.0;
    double SumOfTotalSalesPricesE = 0.0;
    double SumOfTotalSalesPricesS = 0.0;
    double SumOfTotalSalesPricesO = 0.0;

    int northRecordCounter = 0;
    int southRecordCounter = 0;
    int eastRecordCounter = 0;
    int westRecordCounter = 0;
    int otherRecordCounter = 0;


    for (int i=0; i < vShapeCode.size(); i++)
    {
        rad2 = vRadius2.at(i);
        rad1 = vRadius1.at(i);
        hei2 = vHeight2.at(i);
        sCode = vShapeCode.at(i);
        closedBase = vClosedBase.at(i);
        closedTop = vClosedTop.at(i);

        totalSurfaceArea = getTotalSurfaceArea(rad2, rad1, hei2, sCode, closedBase, closedTop);

    // multiply that to get cost and price – no need to have separate functions.
    // update counts
    // update running totals

        if ( vRegion.at(i) == "North" || vRegion.at(i) == "north")
        {
            totalCostOfRawMaterialsN = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceN = totalCostOfRawMaterialsN + totalCostOfRawMaterialsN*MARKUP;

            SumOfTotalSurfaceAreasN += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsN += totalCostOfRawMaterialsN;
            SumOfTotalSalesPricesN += salesPriceN;
            northRecordCounter++;
        } 
        else if ( vRegion.at(i) == "South" || vRegion.at(i) == "south")
        {
            totalCostOfRawMaterialsS = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceS = totalCostOfRawMaterialsS + totalCostOfRawMaterialsS*MARKUP;

            SumOfTotalSurfaceAreasS += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsS += totalCostOfRawMaterialsS;
            SumOfTotalSalesPricesS += salesPriceS;
            southRecordCounter++;
        }
        else if ( vRegion.at(i) == "East" || vRegion.at(i) == "east")
        {
            totalCostOfRawMaterialsE = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceE = totalCostOfRawMaterialsE + totalCostOfRawMaterialsE*MARKUP;

            SumOfTotalSurfaceAreasE += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsE += totalCostOfRawMaterialsE;
            SumOfTotalSalesPricesE += salesPriceE;
            eastRecordCounter++;
        }
        else if ( vRegion.at(i) == "West" || vRegion.at(i) == "west")
        {
            totalCostOfRawMaterialsW = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceW = totalCostOfRawMaterialsW + totalCostOfRawMaterialsW*MARKUP;

            SumOfTotalSurfaceAreasW += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsW += totalCostOfRawMaterialsW;
            SumOfTotalSalesPricesW += salesPriceW;
            westRecordCounter++;
        }
        else if ( vRegion.at(i) == "Other" || vRegion.at(i) == "other")
        {
            totalCostOfRawMaterialsO = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceO = totalCostOfRawMaterialsO + totalCostOfRawMaterialsO*MARKUP;

            SumOfTotalSurfaceAreasO += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsO += totalCostOfRawMaterialsO;
            SumOfTotalSalesPricesO += salesPriceO;
            otherRecordCounter++;
        }

    } // END for

    cout << endl << endl;

    cout << setw(W_R4) << left << "Region";
    cout << setw(W_R2) << right << "Total" << setw(W_R3) << right << "Total" 
    << setw(W_R3) << right << "Total" << endl;
    cout << setw(W_R4) << left << "Code ";
    cout << setw(W_R2) << right << "Area" << setw(W_R5) << right << "Cost " 
    << setw(W_R3) << right << "Price" << endl;

    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    cout << setfill(' ');
   

    cout << setw(W_R4) << right << "South" << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasS << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsS << setw(W_R3) << right 
    << SumOfTotalSalesPricesS << endl;

    cout << setw(W_R4) << right << "West " << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasW << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsW << setw(W_R3) << right 
    << SumOfTotalSalesPricesW << endl;

    cout << setw(W_R4) << right << "North" << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasN << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsN << setw(W_R3) << right 
    << SumOfTotalSalesPricesN << endl;

    cout << setw(W_R4) << right << "East " << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasE << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsE << setw(W_R3) << right 
    << SumOfTotalSalesPricesE << endl;

    cout << setw(W_R4) << right << "Other" << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasO << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsO << setw(W_R3) << right 
    << SumOfTotalSalesPricesO << endl;


    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    cout << setfill(' ');

    cout << setw(W_R1) << left << "Average" << setprecision(2);
    cout << setw(W_R6) << fixed << right 
    << (SumOfTotalSurfaceAreasN+SumOfTotalSurfaceAreasS+SumOfTotalSurfaceAreasE+
        SumOfTotalSurfaceAreasW+SumOfTotalSurfaceAreasO)/(northRecordCounter+
        southRecordCounter+eastRecordCounter+westRecordCounter+otherRecordCounter) 
    << setw(W_R3) << right 
    << (SumOfTotalCostOfRawMaterialsN+SumOfTotalCostOfRawMaterialsS+
        SumOfTotalCostOfRawMaterialsE+SumOfTotalCostOfRawMaterialsW+
        SumOfTotalCostOfRawMaterialsO)/(northRecordCounter+southRecordCounter+
        eastRecordCounter+westRecordCounter+otherRecordCounter)
    << setw(W_R3) << right << (SumOfTotalSalesPricesN+SumOfTotalSalesPricesS+
        SumOfTotalSalesPricesE+SumOfTotalSalesPricesW+SumOfTotalSalesPricesO)/
        (northRecordCounter+southRecordCounter+eastRecordCounter+
        westRecordCounter+otherRecordCounter)
    << endl;

    cout << endl;


} // end summaryByRegion()

void summaryByShape( const vector<string> &vRegion, const vector<char> &vShapeCode,
        const vector<char> &vColorCode, const vector<double> &vRadius2,
        const vector<double> &vRadius1, const vector<double> &vHeight2,
        const vector<char> &vClosedBase, const vector<char> &vClosedTop)
{

    // define variables
    // initialize variables, all the counters and running totals

    double r2 = 0.0;
    double r1 = 0.0;
    double h2 = 0.0;
    char sCode = '?';
    char closedBase = '?';
    char closedTop = '?';
    double totalSurfaceArea = '?';

    double totalCostOfRawMaterialsC = 0.0;
    double totalCostOfRawMaterialsF = 0.0;
    double salesPriceC = 0.0;
    double salesPriceF = 0.0;
    double SumOfTotalSurfaceAreasC = 0.0;
    double SumOfTotalSurfaceAreasF = 0.0;
    double SumOfTotalCostOfRawMaterialsC = 0.0;
    double SumOfTotalCostOfRawMaterialsF = 0.0;
    double SumOfTotalSalesPricesC = 0.0;
    double SumOfTotalSalesPricesF = 0.0;
    int coneRecordCounter = 0;
    int frustumRecordCounter = 0;


    for (int i=0; i < vShapeCode.size(); i++)
    {
        r2 = vRadius2.at(i);
        r1 = vRadius1.at(i);
        h2 = vHeight2.at(i);
        sCode = vShapeCode.at(i);
        closedBase = vClosedBase.at(i);
        closedTop = vClosedTop.at(i);

        totalSurfaceArea = getTotalSurfaceArea(r2, r1, h2, sCode, closedBase, closedTop);

    // multiply that to get cost and price – no need to have separate functions.
    // update counts
    // update running totals

        if ( vShapeCode.at(i) == 'C' || vShapeCode.at(i) == 'c')
        {
            totalCostOfRawMaterialsC = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceC = totalCostOfRawMaterialsC + totalCostOfRawMaterialsC*MARKUP;

            SumOfTotalSurfaceAreasC += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsC += totalCostOfRawMaterialsC;
            SumOfTotalSalesPricesC += salesPriceC;
            coneRecordCounter++;
        } 
        else if ( vShapeCode.at(i) == 'F' || vShapeCode.at(i) == 'f')
        {
            totalCostOfRawMaterialsF = totalSurfaceArea*COST_OF_RAW_MATERIALS;
            salesPriceF = totalCostOfRawMaterialsF + totalCostOfRawMaterialsF*MARKUP;

            SumOfTotalSurfaceAreasF += totalSurfaceArea;
            SumOfTotalCostOfRawMaterialsF += totalCostOfRawMaterialsF;
            SumOfTotalSalesPricesF += salesPriceF;
            frustumRecordCounter++;
        }


    }

// output the table 
    
    cout << endl << endl;

    cout << setw(W_R1) << left << "Shape";
    cout << setw(W_R2) << right << "Total" << setw(W_R3) << right << "Total" 
    << setw(W_R3) << right << "Total" << endl;
    cout << setw(W_R4) << left << "Code ";
    cout << setw(W_R2) << right << "Area" << setw(W_R5) << right << "Cost " 
    << setw(W_R3) << right << "Price" << endl;

    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    cout << setfill(' ');
   

    cout << setw(W_R4) << left << "C" << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasC << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsC << setw(W_R3) << right 
    << SumOfTotalSalesPricesC << endl;

    cout << setw(W_R4) << left << "F" << setprecision(2);
    cout << setw(W_R3) << fixed << right << SumOfTotalSurfaceAreasF << setw(W_R3) 
    << right << SumOfTotalCostOfRawMaterialsF << setw(W_R3) << right 
    << SumOfTotalSalesPricesF << endl;

    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    cout << setfill(' ');

    cout << setw(W_R1) << left << "Average" << setprecision(2);
    cout << setw(W_R6) << fixed << right 
    << (SumOfTotalSurfaceAreasC+SumOfTotalSurfaceAreasF)/(coneRecordCounter+frustumRecordCounter) 
    << setw(W_R3) << right 
    << (SumOfTotalCostOfRawMaterialsC+SumOfTotalCostOfRawMaterialsF)/
    (coneRecordCounter+frustumRecordCounter)
    << setw(W_R3) << right << (SumOfTotalSalesPricesC+SumOfTotalSalesPricesF)/
    (coneRecordCounter+frustumRecordCounter) << endl;

    cout << endl;

}  // end summaryByShape()
