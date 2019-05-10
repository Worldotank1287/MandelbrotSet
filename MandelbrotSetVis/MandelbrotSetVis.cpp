#include "pch.h"			//critical for compilation
#include "superfloat.cpp"	//Theoretically program for adding floats (might be removed)
// this is a tester
#include <SFML/Graphics.hpp>//Required for drawing graphics
#include <array>			//standard array library
#include <vector>			//standard list library
#include <bitset>			//standard library for defining your own data types
#include <thread>			//standard library for multithreading (only works in VS apparently)
#include <iostream> // only for debug purposes

static constexpr int IMAGE_WIDTH = 1000;
static constexpr int IMAGE_HEIGHT = 500;
static double somethingcheckconst = 4.0;

class Mandelbrot {
public:
	Mandelbrot();
	void updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const;
private:
	static const int MAX = 127; // maximum number of iterations for mandelbrot() was 127	Appears to only have to do with color.
						 // don't increase MAX or the colouring will look strange also, CPU is maxed out.
						 // My guess is that regardless of what is visible to the user the program calculates the position of every further interation of the fractal.
						 // EXTREMELY resource inefficient. We will need to change this somehow, and I thought RAM would be our problem, apparently not.
	std::array<sf::Color, MAX + 1> colors;

	int mandelbrot(double startReal, double startImag) const;
	sf::Color getColor(int iterations) const;
	void updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image& image, int minY, int maxY) const;
};

Mandelbrot::Mandelbrot() {				//main method of class
	for (int i = 0; i <= MAX; ++i) {
		colors[i] = getColor(i);
	}
}

int Mandelbrot::mandelbrot(double startReal, double startImag) const {	//where the real math happens
	double zReal = startReal;	//switch these out with superfloats
	double zImag = startImag;

	for (int counter = 0; counter < MAX; ++counter) {

		double r2 = zReal * zReal;	//Complete superfloat multiplication here
		double i2 = zImag * zImag;
		
		if (r2 + i2 > somethingcheckconst) {	//Would have to convert superfloat into something comparable Note: was initially 4.0
			return counter;
		}
		zImag = 2.0 * zReal * zImag + startImag;	//Need more superfloat multiplication, set up superfloat addition
		zReal = r2 - i2 + startReal;
	}
	return MAX;
}

sf::Color Mandelbrot::getColor(int iterations) const {				//getColor method in class Mandelbrot
	int r, g, b;
	int seconditerations = iterations;

	while (seconditerations > 127) seconditerations -= 127;		//Doesn't fix coloration issue.

	// colour gradient:      Red -> Blue -> Green -> Red -> Black
	// corresponding values:  0  ->  16  ->  32   -> 64  ->  127 (or -1)
	if (iterations < 16) {
		r = 16 * (16 - iterations);
		g = 0;
		b = 16 * iterations - 1;
	}
	else if (iterations < 32) {
		r = 0;
		g = 16 * (iterations - 16);
		b = 16 * (32 - iterations) - 1;
	}
	else if (iterations < 64) {
		r = 8 * (iterations - 32);
		g = 8 * (64 - iterations) - 1;
		b = 0;
	}
	else { // range is 64 - 127
		r = 255 - (iterations - 64) * 4;
		g = 0;
		b = 0;
	}
	return sf::Color(r, g, b);
}

void Mandelbrot::updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image& image, int minY, int maxY) const
{		//Yet another Method
	double real = 0 * zoom - IMAGE_WIDTH / 2.0 * zoom + offsetX;
	double imagstart = minY * zoom - IMAGE_HEIGHT / 2.0 * zoom + offsetY;
	for (int x = 0; x < IMAGE_WIDTH; x++, real += zoom) {
		double imag = imagstart;
		for (int y = minY; y < maxY; y++, imag += zoom) {
			int value = mandelbrot(real, imag);
			image.setPixel(x, y, colors[value]);
		}
	}
}

void Mandelbrot::updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const
{		//Other publically defined method of Mandelbrot, last method in list.
	const int STEP = IMAGE_HEIGHT / std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	for (int i = 0; i < IMAGE_HEIGHT; i += STEP) {
		threads.push_back(std::thread(&Mandelbrot::updateImageSlice, *this, zoom, offsetX, offsetY, std::ref(image), i, std::min(i + STEP, IMAGE_HEIGHT)));
	}
	for (auto &t : threads) {
		t.join();
	}
}

int main() {		//Main method
	double offsetX = -0.7; // and move around
	double offsetY = 0.0;
	double zoom = 0.004; // allow the user to zoom in and out...
	double zoomcounter = 1;



	// Example code for SuperFloat class Needs serious updating and replacement
	/*int z = 5;
	std::bitset<8> test1 = 7;
	std::bitset<8> test2 = 8;
	std::vector<std::bitset<8>> initDigits = {test1, test2};
	SuperFloat superTest(z, initDigits);
	printf("%d\n", superTest.getZeros());
	for (std::vector<std::bitset<8>>::const_iterator i = initDigits.begin(); i != initDigits.end(); ++i)
		std::cout << *i << ' ';
	printf("\n");
	//*/
	
	SuperFloat *programtest = new SuperFloat();
	programtest->addDigits(12.3456789);

	Mandelbrot mb;	//Define mandelbrot object

	sf::RenderWindow window(sf::VideoMode(IMAGE_WIDTH, IMAGE_HEIGHT), "Mandelbrot");	//Defines new Window
	window.setFramerateLimit(0);

	sf::Image image;
	image.create(IMAGE_WIDTH, IMAGE_HEIGHT, sf::Color(0, 0, 0));
	sf::Texture texture;
	sf::Sprite sprite;

	bool stateChanged = true; // track whether the image needs to be regenerated

	while (window.isOpen()) {	//Event capturer for program.
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				stateChanged = true; // image needs to be recreated when the user changes zoom or offset
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Equal:
					zoom *= 0.9;
					zoomcounter /= 0.9;
					printf("Zoom: %.30f\n", zoomcounter);
					break;
				case sf::Keyboard::Dash:
					zoom /= 0.9;
					zoomcounter *= 0.9;
					printf("Zoom: %.30f\n", zoomcounter);
					break;
				case sf::Keyboard::W:
					offsetY -= 40 * zoom;	//Maybe replace zoom with a function
					break;
				case sf::Keyboard::S:
					offsetY += 40 * zoom;
					break;
				case sf::Keyboard::A:
					offsetX -= 40 * zoom;
					break;
				case sf::Keyboard::D:
					offsetX += 40 * zoom;
					break;
				case sf::Keyboard::N:
					somethingcheckconst -= 0.1;
					std::cout << "Event Horizon: " << somethingcheckconst << "\n";
					break;
				case sf::Keyboard::M:
					somethingcheckconst += 0.1;
					std::cout << "Event Horizon: " << somethingcheckconst << "\n";
					break;
				default:
					stateChanged = false;
					break;
				}
			default:
				break;
			}
		}

		if (stateChanged) {		//draws image
			mb.updateImage(zoom, offsetX, offsetY, image);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			stateChanged = false;
		}
		window.draw(sprite);
		window.display();
	}
}


/*
Notes:

anti-aliasing: https://stackoverflow.com/questions/30070348/multithreading-computation-of-mandelbrot-set

Color smoothing thing:
value = toValue * expiter + fromValue * ( 1 - expiter)
Where toValue is the iterations and fromvalue is the iterations +1

Check out shader thing here:
https://www.sfml-dev.org/tutorials/2.0/graphics-shader.php

*/