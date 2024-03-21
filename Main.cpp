#include "Image.h"
#include "Rectangle.h"
#include "ImageProcessing.h"
#include "drawingModule.h"
#include <iostream>
#include <cassert>
#include "Point.h"

using namespace std;

void test_setPixelVal() {
    Image img(2, 2);
    img.setPixelVal(0, 0, 100.0);
    img.setPixelVal(1, 0, -10.0);
    img.setPixelVal(0, 1, 300.0);
    img.setPixelVal(1, 1, 200.0);
    assert(img.getPixelVal(0, 0) == 100);
    assert(img.getPixelVal(1, 0) == 0);
    assert(img.getPixelVal(0, 1) == 255);
    assert(img.getPixelVal(1, 1) == 200);
}

void test_setHeight() {
    Image img(2, 2);
    img.setHeight(3);
    assert(img.height() == 3);
    img.setHeight(0);
    assert(img.height() == 0);
}

void test_setWidth() {
    Image img(2, 2);
    img.setWidth(3);
    assert(img.width() == 3);
    img.setWidth(0);
    assert(img.width() == 0);
}

void testDrawCircle() {
    Image img(5, 5);
    Point center(2, 2);
    int radius = 0;
    unsigned int color = 255;
    drawCircle(img, center, radius, color);

    assert(img.getPixelVal(2, 2) == color);
    assert(img.getPixelVal(2, 3) == color);
    assert(img.getPixelVal(1, 2) == color);
    assert(img.getPixelVal(3, 2) == color);

}

void testDrawLine() {
    Image img(10,10);
    Point p1(1,1);
    Point p2(8,8);
    unsigned int color = 255;
    drawLine(img, p1, p2, color);
    assert(img.getPixelVal(1,1) == color);
    assert(img.getPixelVal(2,2) == color);
    assert(img.getPixelVal(3,3) == color);
    assert(img.getPixelVal(4,4) == color);
    assert(img.getPixelVal(5,5) == color);
    assert(img.getPixelVal(6,6) == color);
    assert(img.getPixelVal(7,7) == color);
    assert(img.getPixelVal(8,8) == color);
}

void test_point_default_constructor()
{
    Point p;
    assert(p.getX() == 0);
    assert(p.getY() == 0);
}

void test_point_parameterized_constructor()
{
    Point p(3, 4);
    assert(p.getX() == 3);
    assert(p.getY() == 4);
}

void testRectangleConstructors() {
    Rectangle r1;
    assert(r1.getX() == 0 && r1.getY() == 0 && r1.getHeight() == 0 && r1.getWidth() == 0);

    Rectangle r2(10, 20, 30, 40);
    assert(r2.getX() == 10 && r2.getY() == 20 && r2.getHeight() == 40 && r2.getWidth() == 30);

}

void testAdjustment() {
    Image src(1, 1);
    src.setPixelVal(0, 0, 100);

    Adjustment adj;
    adj.setContrast(2);
    adj.setBrightness(50);

    Image dst(1, 1);
    adj.process(src, dst);

    assert(dst.getPixelVal(0, 0) == 250);
}

void testGamma() {
    Image src(1, 1);
    src.setPixelVal(0, 0, 2);

    Gamma gamma;
    gamma.setTita(3);

    Image dst(1, 1);
    gamma.process(src, dst);

    assert(dst.getPixelVal(0, 0) == 8);
}


int main() {
    {
        test_setHeight();
        test_setPixelVal();
        test_setWidth();
        testDrawCircle();
        testDrawLine();
        testRectangleConstructors();
        test_point_default_constructor();
        test_point_parameterized_constructor();
        testGamma();
        testAdjustment();
        std::cout << "All tests passed.\n";
    }
	{
	Image x;

	x.load("/Users/local.user/Desktop/baboon.ascii.pgm");

	//BRIGHTNESS
	Adjustment adj;
	cout << "1. Making an image darker:" << endl;
	adj.setBrightness(-60);
	adj.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted1.ascii.pgm");
	cout << "2. Making an image brighter:" << endl;
	adj.setBrightness(120);
	adj.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted2.ascii.pgm");

	adj.setBrightness(0);

	//CONTRAST
	cout << "3. Lowering the contrast of an image:" << endl;
	adj.setContrast(0.1);
	adj.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted3.ascii.pgm");

	cout << "4. Giving an image more contrast:" << endl;
	adj.setContrast(10);
	adj.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted4.ascii.pgm");

	adj.setContrast(1);

	//GAMMA CORRECTION
	Gamma gm;
	cout << "5. Gamma correcting the image:" << endl;
	gm.setTita(1);
	gm.process(x,x);
	x.save("/Users/local.user/Desktop/Resulted5.ascii.pgm");

	gm.setTita(1);

	//IMAGE CONVOLUTION
	Convolution con;
	cout << "6. Applying the identity kernel to the image:" << endl;
	con.setOperation(0);
	con.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted6.ascii.pgm");
	cout << "7. Applying mean blur to the image:" << endl;
	con.setOperation(1);
	con.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted7.ascii.pgm");

	cout << "8. Applying Gaussian blur to the image:" << endl;
	con.setOperation(2);
	con.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted8.ascii.pgm");

	cout << "9. Applying the horizontal Sobel kernel to the image:" << endl;
	con.setOperation(3);
	con.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted9.ascii.pgm");

	cout << "10. Applying the vertical Sobel kernel to the image:" << endl;
	con.setOperation(4);
	con.process(x, x);
	x.save("/Users/local.user/Desktop/Resulted10.ascii.pgm");

	//DRAWING
	Rectangle r(100, 100, 100, 130);
	Point P1(200, 321), P2(460, 340);
	cout << "11. Drawing shapes on the image:" << endl;
	drawCircle(x, P1, 100, 0);
	drawLine(x, P1, P2, 0);
	drawRectangle(x, r, 0);
	drawRectangle(x, P1, P2, 0);
	x.save("/Users/local.user/Desktop/Resulted11.ascii.pgm");

	}

	return 0;
}
