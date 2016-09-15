/**
 *
 * jmi34P2.cpp
 *
 * COSC 051 Summer 2016
 * Project #2
 *
 * Due on: JUL 25, 2016
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

const string OPEN_FILE_PROMPT = "Please type in the path and name of the file you wish to open:";
const string OPEN_FILE_ERROR = "File failed to open. Processing cannot continue.";
const string OPEN_FILE_ERROR_2 = " Check the path and the name. Progam will exit.\n";
const string OPEN_FILE_SUCCESS = " opened successfully!\n";

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

const string THANK_YOU_MESSAGE = "Thank you for using AIM Software. We hope you ";
const string THANK_YOU_MESSAGE_2 = "enjoyed using our software.";

// constants to use for column width and other table formatting
const int W_H1 = 45;
const int W_C2 = 4;
const int W_C3 = 22;
const int W_C4 = 8;
const int W_C5 = 18;
const int W_C6 = 6;
const int W_C7 = 19;

const int L1 = 76;
const int L2 = 90;


int main(int argc, const char * argv[])
{

/* --------------------------------------------
--------- DECLARE LOCAL VARIABLES - -----------
----------------------------------------------*/

    char    shapeType               = '?';
    char    colorCode               = '?';
    double  minBaseRadiusFrustum    = 0.0;
    double  maxBaseRadiusFrustum    = 0.0;
    double  theta                   = 0.0;

    // dimension variables

    double  radiusTop               = 0.0;
    double  radiusBase              = 0.0;
    double  heightGF                = 0.0;
    double  heightGC                = 0.0;
    double  height                  = 0.0;
    char    baseOpen                = '?';
    char    topOpen                 = '?';
    double  baseSurfaceArea         = 0.0;
    double  topSurfaceArea          = 0.0;
    double  lateralSurfaceArea      = 0.0;
    double  totalSurfaceAreaC       = 0.0;
    double  totalSurfaceAreaF       = 0.0;
    double  SumOfTotalSurfaceAreasC = 0.0;
    double  SumOfTotalSurfaceAreasF = 0.0;
    // cost and price variables

    double totalCostOfRawMaterialsC = 0.0;
    double totalCostOfRawMaterialsF = 0.0;
    double SumOfTotalCostOfRawMaterialsC = 0.0;
    double SumOfTotalCostOfRawMaterialsF = 0.0;
    double salesPriceC              = 0.0;
    double salesPriceF              = 0.0;
    double SumOfTotalSalesPricesC   = 0.0;
    double SumOfTotalSalesPricesF   = 0.0;
     
    // file handling and formatting variables

    string dataFileName = "";
    string  oneLine = "";

    // Extracted (Ext suffixed) variables
    
    int oYear = 0;
    int oMonth = 0;
    int oDay = 0;
    char chExt = '?';
    int dYear = 0;
    int dMonth = 0;
    int dDay = 0;
    string orderNumberExt = "";
    string stateCodeExt = "";
    string regionExt = "";
    char shapeCodeExt = '?';
    char colorCodeExt = '?';
    float baseRadiusExt = 0.0;
    float topRadiusExt = 0.0;
    float heightExt = 0.0;
    char baseClosedExt = '?';
    char topClosedExt = '?';
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

   

/* -----------------------------------------
------------ OPEN FILE AND CHECK -----------
------------------------------------------*/

    ifstream inFile; 

    cout << WELCOME_MESSAGE << WELCOME_MESSAGE_2 << WELCOME_MESSAGE_3 << WELCOME_MESSAGE_4;
    cout << endl;
    cout << OPEN_FILE_PROMPT << endl;
    cin >> dataFileName;

    inFile.open(dataFileName.c_str());

    if (!inFile)
    {
        cout << OPEN_FILE_ERROR << OPEN_FILE_ERROR_2;
        cout << dataFileName << endl;
    } 
    else
    {
        cout << dataFileName << OPEN_FILE_SUCCESS;

// -------------- READ ADMIN INFO --------

    getline(inFile, oneLine); // read the admin information
    
    // cout << oneLine << endl;   

/* ----------------------------------------
------------ TABLE FOR OUTPUT 2 -----------
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

    while ( inFile >> oYear >> chExt >> oMonth >> chExt >> oDay >> dYear >> chExt >> dMonth &&
            inFile >> chExt >> dDay >> orderNumberExt >> stateCodeExt >> regionExt &&
            inFile >> shapeCodeExt >> colorCodeExt >> baseRadiusExt >> topRadiusExt &&
            inFile >> heightExt >> baseClosedExt >> topClosedExt && getline(inFile, shipToExt))
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

        }

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


        }

        /*------------------ SET BASE RADIUS -------------------*/
        
        if ( baseRadiusExt < MIN_BASE_RADIUS || baseRadiusExt > MAX_BASE_RADIUS)
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

            minBaseRadiusFrustum = 0.5*baseRadiusExt;
            maxBaseRadiusFrustum = 0.75*baseRadiusExt;

        }
    
        /*-------------------SET TOP RADIUS  -------------------*/
    
        if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
        {

            topRadiusErrorMessage = "";
            atLeastOneErrorFlag4 = false;
            frustumRecordWithNoError4 = false;

            if ( topRadiusExt < minBaseRadiusFrustum || topRadiusExt > maxBaseRadiusFrustum )
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
            
        }

        /*-------------------SET HEIGHT ------------------------*/

        if ( heightExt < MIN_SHAPE_HEIGHT || heightExt > MAX_SHAPE_HEIGHT || heightExt < 
            baseRadiusExt ) 
        {
            heightErrorMessage = HEIGHT_ERROR;
            atLeastOneErrorFlag5 = true;
            coneRecordWithNoError5 = false;
            frustumRecordWithNoError5 = false;

        } else {

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


        }

        /*-------------------SET BASE CLOSED -------------------*/

        if ( baseClosedExt != 'Y' && baseClosedExt != 'y' && baseClosedExt !='N' 
            && baseClosedExt !='n')
        {
            
            baseClosedErrorMessage = BASE_CLOSED_ERROR;
            atLeastOneErrorFlag6 = true;
            coneRecordWithNoError6 = false;
            frustumRecordWithNoError6 = false;

        
        } else {

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

        }


        /*-------------------SET TOP CLOSED -------------------*/
        // Do you count Cone records with errors in this field as failing validaation?


        if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
        {

            topClosedErrorMessage = "";
            atLeastOneErrorFlag7 = false;
            frustumRecordWithNoError7 = false;

            if ( topClosedExt != 'Y' && topClosedExt != 'y' && topClosedExt !='N' 
                && topClosedExt !='n')
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
            
        }


        
        /*----------------CALCULATE GC, GF, and theta----------------*/
        if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
            || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
            || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
            || atLeastOneErrorFlag7 == true)  
        {

            heightGF = 0;
            heightGC = 0;
            theta = 0;

        } else
        {      

            if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
            {
            
            heightGF = sqrt(pow((topRadiusExt * heightExt) / (baseRadiusExt - topRadiusExt), 2) +
            pow(topRadiusExt, 2)) + sqrt( pow(heightExt, 2) + pow((baseRadiusExt - topRadiusExt), 
            2));
            heightGC = 0; 
            theta = THETA_MULTIPLE*((2*baseRadiusExt) / (heightGF));


            } else if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
            {

            heightGC = sqrt(pow((topRadiusExt * heightExt) / (baseRadiusExt - topRadiusExt), 2) +
                           pow(topRadiusExt, 2));
            heightGF = sqrt(pow((topRadiusExt * heightExt) / (baseRadiusExt - topRadiusExt), 2) + 
                           pow(topRadiusExt, 2)) + sqrt( pow(heightExt, 2) + pow((baseRadiusExt - 
                           topRadiusExt), 2));
            theta = THETA_MULTIPLE*((2*baseRadiusExt - 2*topRadiusExt) / (heightGF - heightGC));

            } else 
            {

            heightGC = 0;
            heightGF = 0;
            theta = 0;

            }
        }

        /*--------CALCULATE TOTAL AREA,COST,PRICE ----------------*/

        if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
            || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
            || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
            || atLeastOneErrorFlag7 == true)  
        {

            lateralSurfaceArea = 0;
            topSurfaceArea = 0;
            baseSurfaceArea = 0;

        } else {        
        
            if ( shapeCodeExt == 'F' || shapeCodeExt == 'f')
            {
                lateralSurfaceArea = PI*(topRadiusExt+baseRadiusExt)*sqrt(pow(heightExt,2)+
                pow((baseRadiusExt - topRadiusExt),2));

                if ( topClosedExt == 'Y' || topClosedExt == 'y')
                {
                    topSurfaceArea = PI*pow(topRadiusExt,2);
                } else
                {
                    topSurfaceArea = 0;
                }

                if ( baseClosedExt == 'Y' || baseClosedExt == 'y')
                {
                    baseSurfaceArea = PI*pow(baseRadiusExt,2);     
                } else
                {
                    baseSurfaceArea = 0;
                }
            
            } else if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
            {
                lateralSurfaceArea = PI*baseRadiusExt*sqrt(pow(baseRadiusExt,2)+pow(heightExt,2));
                topSurfaceArea = 0;

                if ( baseClosedExt == 'Y' || baseClosedExt == 'y')
                {
                    baseSurfaceArea = PI*pow(baseRadiusExt,2);
                } else
                {
                    baseSurfaceArea = 0;
                }
            }
        }

        // perform general calculations that have not yet been performed
        

        if ( shapeCodeExt == 'C' || shapeCodeExt == 'c')
        {

        totalSurfaceAreaC = lateralSurfaceArea + topSurfaceArea + baseSurfaceArea;
        totalCostOfRawMaterialsC = totalSurfaceAreaC*COST_OF_RAW_MATERIALS;
        salesPriceC = totalCostOfRawMaterialsC + totalCostOfRawMaterialsC*MARKUP;

        SumOfTotalSurfaceAreasC += totalSurfaceAreaC;
        SumOfTotalCostOfRawMaterialsC += totalCostOfRawMaterialsC;
        SumOfTotalSalesPricesC += salesPriceC;

        } else if (shapeCodeExt == 'F' || shapeCodeExt == 'f')
        {
        
        totalSurfaceAreaF = lateralSurfaceArea + topSurfaceArea + baseSurfaceArea;
        totalCostOfRawMaterialsF = totalSurfaceAreaF*COST_OF_RAW_MATERIALS;
        salesPriceF = totalCostOfRawMaterialsF + totalCostOfRawMaterialsF*MARKUP;

        SumOfTotalSurfaceAreasF += totalSurfaceAreaF;
        SumOfTotalCostOfRawMaterialsF += totalCostOfRawMaterialsF;
        SumOfTotalSalesPricesF += salesPriceF;

        }

        lateralSurfaceArea = 0;
        topSurfaceArea = 0;
        baseSurfaceArea = 0;
        totalSurfaceAreaC = 0;
        totalSurfaceAreaF = 0;
        totalCostOfRawMaterialsC = 0;
        totalCostOfRawMaterialsF = 0;
        salesPriceC = 0;
        salesPriceF = 0;


    // report counters

        if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
            || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
            || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
            || atLeastOneErrorFlag7 == true)  
        {
            atLeastOneErrorCounter++;
        }

        if (coneRecordWithNoError2 == true && coneRecordWithNoError3 == true 
            && coneRecordWithNoError5 == true && coneRecordWithNoError6 == true)
        {
            coneRecordCounter++;
            coneRecordWithNoError2 = false;
            coneRecordWithNoError3 = false;
            coneRecordWithNoError5 = false;
            coneRecordWithNoError6 = false;

        }

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
        }
        
        //
        totalRecordCounter++;

        shapeCodeToUpper = toupper(shapeCodeExt);
        colorCodeToUpper = toupper(colorCodeExt);
        baseClosedToUpper = toupper(baseClosedExt);
        topClosedToUpper = toupper(topClosedExt);


        if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
            || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
            || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
            || atLeastOneErrorFlag7 == true)  
        {
        
            if ( topRadiusExt == 0)
            {
            
                cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                << right << baseRadiusExt << setw(W_C4) << "n/a" << setw(W_C4) 
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
                << right << baseRadiusExt << setw(W_C4) << topRadiusExt << setw(W_C4) 
                << heightExt << setw(W_C4) << right << baseClosedToUpper
                << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                << fixed << "" << setw(W_C4) << "" << setw(W_C4) << setprecision(3) << "";   
                cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                << topClosedErrorMessage << endl;
                
                cout << endl;

            }
    

        } else {

            if ( heightGC == 0 && topRadiusExt != 0)
            {
                cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) << 
                colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                << right << baseRadiusExt << setw(W_C4) << topRadiusExt << setw(W_C4) 
                << heightExt << setw(W_C4) << right << baseClosedToUpper
                << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                << fixed << "n/a" << setw(W_C4) << heightGF << setw(W_C4) << setprecision(3) 
                << theta;   
                cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                << topClosedErrorMessage << endl;

            } else if ( heightGC != 0 && topRadiusExt == 0)

            {

                cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                << right << baseRadiusExt << setw(W_C4) << "n/a" << setw(W_C4) 
                << heightExt << setw(W_C4) << right << baseClosedToUpper
                << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                << fixed << heightGC << setw(W_C4) << heightGF << setw(W_C4) 
                << setprecision(3) << theta;   
                cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                << topClosedErrorMessage << endl;


            } else if ( heightGC == 0 && topRadiusExt == 0)

            {

                cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                << right << baseRadiusExt << setw(W_C4) << "n/a" << setw(W_C4) 
                << heightExt << setw(W_C4) << right << baseClosedToUpper << setw(W_C4) 
                << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                << fixed << "n/a" << setw(W_C4) << heightGF << setw(W_C4) 
                << setprecision(3) << theta;   
                cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                << topClosedErrorMessage << endl;


            } else 

            {
              
                cout << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
                << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
                << right << baseRadiusExt  << setw(W_C4) << topRadiusExt 
                << setw(W_C4) << heightExt << setw(W_C4) << right << baseClosedToUpper 
                << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
                << fixed << heightGC << setw(W_C4) << heightGF << setw(W_C4) 
                << setprecision(3) << theta;   
                cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                << topClosedErrorMessage << endl;

            }


        }


        
    } // END While loop

    cout << endl;
    cout << setw(W_C4) << right << totalRecordCounter << setw(W_C4) << left << TOTAL_RECORDS;
    cout << setw(W_C4) << right << atLeastOneErrorCounter << setw(W_C4+W_C4+W_C4) << left 
    << RECORDS_WITH_ONE_INVALID_VALUE;
    cout << setw(W_C4) << right << coneRecordCounter << setw(W_C4+W_C4+W_C4) << left 
    << CONE_RECORDS_NO_ERRORS;
    cout << setw(W_C4) << right << frustumRecordCounter << setw(W_C4+W_C4+W_C4) << left 
    << FRUSTUM_RECORDS_NO_ERRORS;
    cout << endl;

/*  cout << left << setw(W_C4) << "C" << setw(W_C4) << "I" << setw(W_C4) << "19.73" 
    << setw(W_C4) << "n/a" << setw(W_C4) << "20.70" << setw(W_C4) << right << "N" 
    << setw(W_C4) << "Y" << setw(W_C4) << right << "40.99" << setw(W_C4) << "28.60" 
    << setw(W_C4) << "248.38" << endl;   
*/


/* ----------------------------------------
------------ TABLE FOR OUTPUT 3 -----------
-----------------------------------------*/

    cout << endl << endl;

    cout << setw(W_C2) << left << "Shape";
    cout << setw(W_C5) << right << "Total" << setw(W_C3) << right << "Total" 
    << setw(W_C3) << right << "Total" << endl;
    cout << setw(W_C2) << left << "Code";
    cout << setw(W_C5) << right << "Area" << setw(W_C3) << right << "Cost" 
    << setw(W_C3) << right << "Price" << endl;

    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    // set fill fills the spaces equal to the width defined followin it 
    cout << setfill(' ');
   

    cout << setw(W_C2) << left << "C" << setprecision(2);
    cout << setw(W_C3) << fixed << right << SumOfTotalSurfaceAreasC << setw(W_C3) 
    << right << SumOfTotalCostOfRawMaterialsC << setw(W_C3) << right 
    << SumOfTotalSalesPricesC << endl;

    cout << setw(W_C2) << left << "F" << setprecision(2);
    cout << setw(W_C3) << fixed << right << SumOfTotalSurfaceAreasF << setw(W_C3) 
    << right << SumOfTotalCostOfRawMaterialsF << setw(W_C3) << right 
    << SumOfTotalSalesPricesF << endl;

    cout << setfill('-') << setw(L1) << "-" <<  endl; 
    // set fill fills the spaces equal to the width defined followin it 
    cout << setfill(' ');

    cout << setw(W_C6) << left << "Average" << setprecision(2);
    cout << setw(W_C7) << fixed << right 
    << (SumOfTotalSurfaceAreasC+SumOfTotalSurfaceAreasF)/(coneRecordCounter+frustumRecordCounter) 
    << setw(W_C3) << right 
    << (SumOfTotalCostOfRawMaterialsC+SumOfTotalCostOfRawMaterialsF)/
    (coneRecordCounter+frustumRecordCounter)
    << setw(W_C3) << right << (SumOfTotalSalesPricesC+SumOfTotalSalesPricesF)/
    (coneRecordCounter+frustumRecordCounter) << endl;

    cout << endl;
 

    }   

    inFile.close();

    return 0;

}
