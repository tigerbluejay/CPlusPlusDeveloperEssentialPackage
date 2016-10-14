
/**
 *
 * jmi34P4.cpp
 *
 * COSC 051 Summer 2016
 * Project #4
 *
 * Due on: AUG 10, 2016
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



/***************************************************************************************
 *                                                                                     *
 *                             class Shape declaraion                                  *
 *    This is provided to COSC 051 students to use as their own without attribution    *
 ***************************************************************************************/

class Shape
{
    // overloaded stream insertion operator
    friend ostream& operator<<( ostream &os, const Shape &rhsObj );
    
    // overloaded stream extraction operator
    friend istream& operator>>( istream &is, Shape &rhsObj );
    
private:
    int orderYear, orderMonth, orderDay, deliveryYear, deliveryMonth, deliveryDay;
    string orderNumber, stateCode, salesRegion;
    char shapeCode, colorCode;
    double radius2, radius1, height2;
    char closedBase, closedTop;
    string customerNameAddress;
    
public:
    double getGC() const;
    double getGF() const;
    double getTheta() const;
    double getTotalSurfaceArea() const;
    double getCost() const;
    double getPrice() const;    

    Shape(); //default constructor
    Shape( int oY, int oM, int oD, int dY, int dM, int dD, string oNum, string stCode,
           string reg, char sC, char cC, double r2, double r1, double h2, 
           char cBase, char cTop, string cNameAdd );
    
    string getOrderDate() const;  
    string getDeliveryDate() const;
    void setOrderDate( int y, int m, int d);
    void setDeliveryDate( int y, int m, int d);
    
    // given accessor functions
    string getOrderNumber() const { return orderNumber; }
    string getStateCode() const { return stateCode; }
    string getSalesRegion() const { return salesRegion; } 
    char getShapeCode() const { return shapeCode; }
    char getColorCode() const { return colorCode; }
    double getRadius2() const { return radius2; }
    double getRadius1() const { return radius1; }
    double getHeight2() const { return height2; }
    char getClosedBase() const { return closedBase; }
    char getClosedTop() const { return closedTop; }
    string getCustomerNameAddress() const { return customerNameAddress; }
    
    // given mutator functions
    void setOrderNumber( string oNum ) { orderNumber = oNum; }
    void setStateCode( string stCode ) { stateCode = stCode; }
    void setSalesRegion( string reg ) { salesRegion = reg; } 
    void setShapeCode( char sC ) { shapeCode = sC; }
    void setColorCode( char cC ) { colorCode = cC; }
    void setRadius2( double r2 ) { radius2 = r2; }
    void setRadius1( double r1 ) { radius1 = r1; }
    void setHeight2( double h2 ) { height2 = h2; }
    void setClosedBase( char cBase ) { closedBase = cBase; }
    void setClosedTop( char cTop ) { closedTop = cTop; }
    void setCustomerNameAddress( string cNameAdd ) { customerNameAddress = cNameAdd; }
    
}; //END declaration for class Shape

Shape::Shape()
{

orderYear = 1981;
orderMonth = 1;
orderDay = 1;
deliveryYear = 1981;
deliveryMonth = 2;
deliveryDay = 2;
orderNumber = 1;
stateCode = 1;
salesRegion = 1;
shapeCode = '?';
colorCode = '?';
radius2 = 0.0;
radius1 = 0.0;
height2 = 0.0;
closedBase = '?';
closedTop = '?';
customerNameAddress = "";


} // end of default constructor


Shape::Shape( int oY, int oM, int oD, int dY, int dM, int dD, string oNum, string stCode,
           string reg, char sC, char cC, double r2, double r1, double h2, 
           char cBase, char cTop, string cNameAdd )
{
    //cout << "indide constructor with parameters for Widget class\n";
    
orderYear = oY;
orderMonth = oM;
orderDay = oD;
deliveryYear = dY;
deliveryMonth = dM;
deliveryDay = dD;
orderNumber = oNum;
stateCode = stCode;
salesRegion = reg;
shapeCode = sC;
colorCode = cC;
radius2 = r2;
radius1 = r1;
height2 = h2;
closedBase = cBase;
closedTop = cTop;
customerNameAddress = cNameAdd;

} //END constructor with parameters for Shape class

ostream& operator<< ( ostream &os, const Shape &rhsObj) 
{

    char shapeCodeToUpper = '?';
    char colorCodeToUpper = '?';
    char baseClosedToUpper = '?';
    char topClosedToUpper = '?';

    shapeCodeToUpper = toupper(rhsObj.shapeCode);
    colorCodeToUpper = toupper(rhsObj.colorCode);
    baseClosedToUpper = toupper(rhsObj.closedBase);
    topClosedToUpper = toupper(rhsObj.closedTop);


    os << left << setw(W_C4) << shapeCodeToUpper << setw(W_C4) 
    << colorCodeToUpper << setw(W_C4) << setprecision(2) << fixed 
    << right << rhsObj.radius2  << setw(W_C4) << rhsObj.radius1 
    << setw(W_C4) << rhsObj.height2 << setw(W_C4) << right << baseClosedToUpper 
    << setw(W_C4) << topClosedToUpper << setw(W_C4) << right << setprecision(2) 
    << fixed << rhsObj.getGC() << setw(W_C4) << rhsObj.getGF() << setw(W_C4) 
    << setprecision(3) << rhsObj.getTheta() << endl;
   
    return os;

}

istream& operator>> ( istream &is, Shape &rhsObj) // rhs right hand side operand
{
    char ch = '?';

    is >> rhsObj.orderYear >> ch >> rhsObj.orderMonth >> ch >> rhsObj.orderDay >>
    rhsObj.deliveryYear >> ch >> rhsObj.deliveryMonth >> ch >> rhsObj.deliveryDay >>
    rhsObj.orderNumber >> rhsObj.stateCode >> rhsObj.salesRegion >> rhsObj.shapeCode >>
    rhsObj.colorCode >> rhsObj.radius2 >> rhsObj.radius1 >> rhsObj.height2 >>
    rhsObj.closedBase >> rhsObj.closedTop && getline(is, rhsObj.customerNameAddress);

    return is; 
}

/*-------------------------------------------------------------------
------------------STANDALONE FUNCTION PROTOTYPES --------------------
--------------------------------------------------------------------*/

char showMenu ();

bool loadData( string fileName, vector<Shape> &vS );

void summaryByRegion( const vector<Shape> &vS);

void summaryByShape( const vector<Shape> &vS);


int main(int argc, const char * argv[])
{
    string fileName = "";
    ifstream inFile;

    
    /* --------------------------------------------
    --------- DECLARE LOCAL VARIABLES - -----------
    ----------------------------------------------*/

    vector<Shape>vShapeList;

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

                    loadWasSuccessful = loadData(fileName, vShapeList);

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

                    summaryByRegion(vShapeList);

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
 
                    summaryByShape(vShapeList);
 
                    break;
                    }

            case 'Q':
            case 'q':

                    break;

            default:
                    cout << "'" << userSelection << "'" << "is not a valid choice.\n" 
                    << VALID_OPTIONS_PROMPT;
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


bool loadData ( string fileName, vector<Shape> &vS)
{

    double  minBaseRadiusFrustum    = 0.0;
    double  maxBaseRadiusFrustum    = 0.0;

    double  heightGF                = 0.0;
    double  heightGC                = 0.0;
    double  angleTheta              = 0.0;

    double gFValue                  = 0.0;
    double gCValue                  = 0.0;
    double thetaValue               = 0.0;

    string  oneLine = "";

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

    char shapeCodeToUpper = '?';
    char colorCodeToUpper = '?';
    char baseClosedToUpper = '?';
    char topClosedToUpper = '?';
    double radiusBaseExt = 0.0;
    double radiusTopExt = 0.0;
    double heightExt = 0.0;

    // counters    
    int coneRecordCounter = 0;
    int frustumRecordCounter = 0;
    int totalRecordCounter = 0;
    int atLeastOneErrorCounter = 0;
    
    bool loadWasSuccessful = false;

    ifstream inFile;

    inFile.open(fileName.c_str());

    if (!inFile)
    {
        cout << endl;
        cout << OPEN_FILE_ERROR << " " << fileName << " " << OPEN_FILE_ERROR_2 
        << OPEN_FILE_ERROR_3;
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

        Shape s1;

            while ( inFile >> s1)
            {
                

               /* ----------------- SET SHAPE ---------------*/
                
                if ( s1.getShapeCode() != 'C' && s1.getShapeCode() != 'c' &&
                     s1.getShapeCode() !='F' && s1.getShapeCode() != 'f')
                {
                    shapeErrorMessage = SHAPE_ERROR;
                    atLeastOneErrorFlag1 = true;
                    

                } else if ( s1.getShapeCode() == 'C' || s1.getShapeCode() == 'c') 
                {
                    shapeErrorMessage = "";
                    atLeastOneErrorFlag1 = false;
     
                } else
                {
                    shapeErrorMessage = "";
                    atLeastOneErrorFlag1 = false;
                    

                } // end if ( shapeCodeExt ...

                /*--------------------- SET COLOR -------------------*/

                if ( s1.getColorCode() != 'R' && s1.getColorCode() != 'r' &&
                 s1.getColorCode() != 'O' && s1.getColorCode() !='o' &&
                 s1.getColorCode() != 'Y' && s1.getColorCode() !='y' && 
                 s1.getColorCode() != 'G' && s1.getColorCode() != 'g' && 
                 s1.getColorCode() != 'B' && s1.getColorCode() != 'b' && 
                 s1.getColorCode() != 'I' && s1.getColorCode() != 'i' && 
                 s1.getColorCode() != 'V' && s1.getColorCode() != 'v')
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

                    if ( s1.getShapeCode() == 'C' || s1.getShapeCode() == 'c')
                    {
                        coneRecordWithNoError2 = true;
                        


                    } else if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                
                    {
                        frustumRecordWithNoError2 = true;

                    }


                } // end if

                /*------------------ SET BASE RADIUS -------------------*/
                
                if ( s1.getRadius2() < MIN_BASE_RADIUS || s1.getRadius2() > MAX_BASE_RADIUS)
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

                    if ( s1.getShapeCode() == 'C' || s1.getShapeCode() == 'c')
                    {
                        coneRecordWithNoError3 = true;
                        


                    } else if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                    {
                        frustumRecordWithNoError3 = true;
                        
                    }

                    minBaseRadiusFrustum = 0.5*s1.getRadius2();
                    maxBaseRadiusFrustum = 0.75*s1.getRadius2();

                } // end if
            
                /*-------------------SET TOP RADIUS  -------------------*/
            
                if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                {

                    topRadiusErrorMessage = "";
                    atLeastOneErrorFlag4 = false;
                    frustumRecordWithNoError4 = false;

                    if ( s1.getRadius1() < minBaseRadiusFrustum || s1.getRadius1() >
                     maxBaseRadiusFrustum )
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

                if ( s1.getHeight2() < MIN_SHAPE_HEIGHT || s1.getHeight2() > MAX_SHAPE_HEIGHT ||
                     s1.getHeight2() < s1.getRadius2() ) 
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

                    if ( s1.getShapeCode() == 'C' || s1.getShapeCode() == 'c')
                    {
                        coneRecordWithNoError5 = true;
                        

                    } else if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                    {
                        frustumRecordWithNoError5 = true;
                    }


                } // end if

                /*-------------------SET BASE CLOSED -------------------*/

                if ( s1.getClosedBase() != 'Y' && s1.getClosedBase() != 'y' &&
                  s1.getClosedBase() !='N' && s1.getClosedBase() !='n')
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

                    if ( s1.getShapeCode() == 'C' || s1.getShapeCode() == 'c')
                    {
                        coneRecordWithNoError6 = true;

                    } else if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                    {
                        frustumRecordWithNoError6 = true;
                    }

                } // end if


                /*-------------------SET TOP CLOSED -------------------*/
            

                if ( s1.getShapeCode() == 'F' || s1.getShapeCode() == 'f')
                {

                    topClosedErrorMessage = "";
                    atLeastOneErrorFlag7 = false;
                    frustumRecordWithNoError7 = false;

                    if ( s1.getClosedTop() != 'Y' && s1.getClosedTop() != 'y' && 
                        s1.getClosedTop() !='N' && s1.getClosedTop() !='n')
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

                    gFValue = s1.getGF();
                    gCValue = s1.getGC();
                    thetaValue = s1.getTheta();

                } // end if
                
                /*------------------- REPORT COUNTERS -----------------------*/

                if (atLeastOneErrorFlag1 == true || atLeastOneErrorFlag2 == true 
                    || atLeastOneErrorFlag3 == true || atLeastOneErrorFlag4 == true 
                    || atLeastOneErrorFlag5 == true || atLeastOneErrorFlag6 == true 
                    || atLeastOneErrorFlag7 == true)  
                {
                    atLeastOneErrorCounter++;
                } else {


                    vS.push_back(s1);

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

                shapeCodeToUpper = toupper(s1.getShapeCode());
                colorCodeToUpper = toupper(s1.getColorCode());
                baseClosedToUpper = toupper(s1.getClosedBase());
                topClosedToUpper = toupper(s1.getClosedTop());
                radiusBaseExt = s1.getRadius2();
                radiusTopExt = s1.getRadius1();
                heightExt = s1.getHeight2();


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
                      
                        cout << s1;   
                        cout << shapeErrorMessage << colorErrorMessage << baseRadiusErrorMessage 
                        << topRadiusErrorMessage << heightErrorMessage << baseClosedErrorMessage 
                        << topClosedErrorMessage << endl;

                    }


            } // end if


                cout << s1;
            
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


double Shape::getGF() const
{


    double heightGF = 0.0;

    heightGF = sqrt(pow((radius1 * height2) / (radius2 - radius1), 2) + pow(radius1, 2)) +
               sqrt( pow(height2, 2) + pow((radius2 - radius1), 2));                   
    
    return heightGF;

} // end getGF()


double Shape::getGC() const
{
     
    double heightGC = 0.0;
    
    heightGC = sqrt(pow((radius1 * height2) / (radius2 - radius1), 2) + pow(radius1, 2));

    return heightGC;

} // end getGC()



double Shape::getTheta() const
{
    // These are intermediate variables that I used in my Project #2
    // cout << "Entered function getTheta()\n";

    double p1 = 0.0, p2 = 0.0;
    
    // I copied the values passed to the function parameters into 
    // additional local variables that matched the variable identifiers
    // used in my Project #2 code you may follow this strategy
    // or you may simply change the identifiers in this function
    // heading to match your Project #2 identifiers
        
    double angleTheta = 0.0;
        
    //calculate angleTheta in several steps
    p1 = ( (2 * radius2) - (2 * radius1) );
    
    // NOTE: This function makes calls to getGF and getGC, you will 
    //       need to implement both of those other functions before
    //       function getTheta will return accurate values
    
    p2 = getGF() - getGC();
    
    angleTheta = 180 * (p1 / p2);    

    // cout << "Exiting function getTheta()\n";

    return angleTheta;
    
} // end getTheta()

  

double Shape::getTotalSurfaceArea() const
{
    
    double lateralSurfaceArea = 0.0;
    double topSurfaceArea = 0.0;
    double baseSurfaceArea = 0.0;
    double totalSurfaceArea = 0.0;


    if ( shapeCode == 'F' || shapeCode == 'f')
        {
        lateralSurfaceArea = PI*(radius1+radius2)*sqrt(pow(height2,2)+pow((radius2 - radius1),2));

        if ( closedTop == 'Y' || closedTop == 'y')
        {
            topSurfaceArea = PI*pow(radius1,2);
        } else
        {
            topSurfaceArea = 0;
        }

        if ( closedBase == 'Y' || closedBase == 'y')
        {
            baseSurfaceArea = PI*pow(radius2,2);     
        } else
        {
            baseSurfaceArea = 0;
        }
    
    } else if ( shapeCode == 'C' || shapeCode == 'c')
    {
        lateralSurfaceArea = PI*radius2*sqrt(pow(radius2,2)+pow(height2,2));
        topSurfaceArea = 0;

        if ( closedBase == 'Y' || closedBase == 'y')
        {
            baseSurfaceArea = PI*pow(radius2,2);
        } else
        {
            baseSurfaceArea = 0;
        }
    } // end if

    
    return totalSurfaceArea = lateralSurfaceArea + topSurfaceArea + baseSurfaceArea;

} // end getTotalSurfaceArea()


double Shape::getCost() const
{

  double totalCostOfRawMaterials = 0.0;

  return totalCostOfRawMaterials = getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;

} // end getTotalSurfaceArea()

double Shape::getPrice() const
{

  double salesPrice = 0.0;

  return salesPrice = getCost() + getCost()*MARKUP;

} // end getTotalSurfaceArea()


void summaryByRegion( const vector<Shape> &vS)
{
    
    // define variables
    // initialize variables, all the counters and running totals

    double totalSurfaceArea = 0.0;

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


    for (int i=0; i < vS.size(); i++)
    {

        totalSurfaceArea = vS[i].getTotalSurfaceArea();

    // multiply that to get cost and price – no need to have separate functions.
    // update counts
    // update running totals

        if ( vS[i].getSalesRegion() == "North" || vS[i].getSalesRegion() == "north")
        {
            totalCostOfRawMaterialsN = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceN = totalCostOfRawMaterialsN + totalCostOfRawMaterialsN*MARKUP;

            SumOfTotalSurfaceAreasN += vS[i].getTotalSurfaceArea();
            SumOfTotalCostOfRawMaterialsN += totalCostOfRawMaterialsN;
            SumOfTotalSalesPricesN += salesPriceN;
            northRecordCounter++;
        } 
        else if ( vS[i].getSalesRegion() == "South" || vS[i].getSalesRegion() == "south")
        {
            totalCostOfRawMaterialsS = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceS = totalCostOfRawMaterialsS + totalCostOfRawMaterialsS*MARKUP;

            SumOfTotalSurfaceAreasS += vS[i].getTotalSurfaceArea();
            SumOfTotalCostOfRawMaterialsS += totalCostOfRawMaterialsS;
            SumOfTotalSalesPricesS += salesPriceS;
            southRecordCounter++;
        }
        else if ( vS[i].getSalesRegion() == "East" || vS[i].getSalesRegion() == "east")
        {
            totalCostOfRawMaterialsE = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceE = totalCostOfRawMaterialsE + totalCostOfRawMaterialsE*MARKUP;

            SumOfTotalSurfaceAreasE += vS[i].getTotalSurfaceArea();
            SumOfTotalCostOfRawMaterialsE += totalCostOfRawMaterialsE;
            SumOfTotalSalesPricesE += salesPriceE;
            eastRecordCounter++;
        }
        else if ( vS[i].getSalesRegion() == "West" || vS[i].getSalesRegion() == "west")
        {
            totalCostOfRawMaterialsW = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceW = totalCostOfRawMaterialsW + totalCostOfRawMaterialsW*MARKUP;

            SumOfTotalSurfaceAreasW += vS[i].getTotalSurfaceArea();
            SumOfTotalCostOfRawMaterialsW += totalCostOfRawMaterialsW;
            SumOfTotalSalesPricesW += salesPriceW;
            westRecordCounter++;
        }
        else if ( vS[i].getSalesRegion() == "Other" || vS[i].getSalesRegion() == "other")
        {
            totalCostOfRawMaterialsO = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceO = totalCostOfRawMaterialsO + totalCostOfRawMaterialsO*MARKUP;

            SumOfTotalSurfaceAreasO += vS[i].getTotalSurfaceArea();
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

void summaryByShape( const vector<Shape> &vS)
{


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


    for (int i=0; i < vS.size(); i++)
    {

    // multiply that to get cost and price – no need to have separate functions.
    // update counts
    // update running totals

        if ( vS[i].getShapeCode() == 'C' || vS[i].getShapeCode() == 'c')
        {
            totalCostOfRawMaterialsC = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceC = totalCostOfRawMaterialsC + totalCostOfRawMaterialsC*MARKUP;

            SumOfTotalSurfaceAreasC += vS[i].getTotalSurfaceArea();
            SumOfTotalCostOfRawMaterialsC += totalCostOfRawMaterialsC;
            SumOfTotalSalesPricesC += salesPriceC;
            coneRecordCounter++;
        } 
        else if ( vS[i].getShapeCode() == 'F' || vS[i].getShapeCode() == 'f')
        {
            totalCostOfRawMaterialsF = vS[i].getTotalSurfaceArea()*COST_OF_RAW_MATERIALS;
            salesPriceF = totalCostOfRawMaterialsF + totalCostOfRawMaterialsF*MARKUP;

            SumOfTotalSurfaceAreasF += vS[i].getTotalSurfaceArea();
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