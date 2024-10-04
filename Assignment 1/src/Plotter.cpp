#include "Plotter.h"
#include "strlib.h"
#include <vector>
#include <stdbool.h>
#include <string>


using namespace std;

struct PenPosition{
    double x;
    double y;
};

void changePosition(double x_1, double y_1, struct PenPosition& position){
    position.x=x_1;
    position.y=y_1;
}

void changeStyle(double width_1, string color_1 , struct PenStyle& style){
    style.width=width_1;
    style.color=color_1;
}

void runPlotterScript(istream& input) {
    //initialize pen status info
    bool Up =true;
    double x_1,y_1;
    PenStyle style={1,"black"};
    PenPosition position={0.0,0.0};

    for(string line; getline(input,line);){
        Vector<string> result= stringSplit(line," ");
        string cmd=result[0];
        cmd=toLowerCase(cmd);

        if(cmd=="pendown"){
            if(Up){
                Up=false;
            }
        }

        if(cmd=="penup"){
            if(!Up){
                Up=true;
            }
        }

        if(cmd=="moveabs"){
            x_1=stringToReal(result[1]);
            y_1=stringToReal(result[2]);
            if(!Up){
                drawLine(position.x,position.y,x_1,y_1,style);
            }
            changePosition(x_1,y_1,position);
        }

        if(cmd=="moverel"){
            x_1=stringToReal(result[1]);
            y_1=stringToReal(result[2]);
            if(!Up){
                drawLine(position.x,position.y,position.x+x_1,position.y+y_1,style);
            }
            changePosition(position.x+x_1,position.y+y_1,position);
        }

        if(cmd=="pencolor"){
            changeStyle(style.width,result[1],style);
        }

        if(cmd=="penwidth"){
            changeStyle(stringToReal(result[1]),style.color,style);
        }

        }


}
