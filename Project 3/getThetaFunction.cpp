

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

double getTheta( double r2, double r1, double h2 )
{
    // These are intermediate variables that I used in my Project #2
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

    return angleTheta;
    
} //END function getTheta
