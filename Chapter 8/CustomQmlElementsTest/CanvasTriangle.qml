import QtQuick 2.0


 Canvas	{
     id: triangle
     property real triangleWidth: width * 0.8;
     property real triangleHeight: height * 0.8

     onPaint:	{
         var ctx = getContext("2d");

         ctx.lineWidth = 4
         ctx.strokeStyle = "blue"
         ctx.fillStyle = "steelblue"

         ctx.beginPath();
         ctx.moveTo(0, 0);
         ctx.lineTo(triangleWidth, 0);
         ctx.lineTo(0.5 * triangleWidth, triangleHeight);
         ctx.closePath();

         ctx.fill()
         ctx.stroke()
     }
 }
