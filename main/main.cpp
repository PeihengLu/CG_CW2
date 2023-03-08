/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>
// testing the elapsed time for rendering
#include <chrono>


#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"


using namespace rt;
using namespace rapidjson;

int main(int argc, char* argv[]){

	auto start_time = std::chrono::high_resolution_clock::now();

	//parse commandline arguments
	char* inputFile=argv[1];    //first command line argument holds the path to the json input file
	char* outputFile=argv[2];   //second command line argument holds the path to the output image file
	char* sampleNum=argv[3]; // third command used for testing sample size

	std::printf("Input file: %s\n",inputFile);
	std::printf("Output file: %s\n",outputFile);

	//parse json input file using rapidjson
	std::ifstream ifs(inputFile);
	IStreamWrapper is(ifs);
	Document d;     // d holds the complete json object
	d.ParseStream(is);

	//generate a camera according to the input file
	Camera* camera=Camera::createCamera(d["camera"], std::stoi(sampleNum));

	//print camera data (based on the input file provided)
	camera->printCamera();

	//generate the scene according to the input file
	Scene* scene=new Scene();
	printf("Creating New Scene\n");
	scene->createScene(d["scene"]);

	//
	// Main function, render scene
	//
	auto start_time_rend = std::chrono::high_resolution_clock::now();
	Vec3f* pixelbuffer=RayTracer::render(camera, scene, d["nbounces"].GetInt());

	int height = camera->height;
	int width = camera->width;



	//free resources when rendering is finished
	delete camera;
	delete scene;



	//convert linear RGB pixel values [0-1] to range 0-255
	RayTracer::tonemap(pixelbuffer, width, height);



	std::printf("Output file: %s\n",outputFile);

	//write rendered scene to file (pixels RGB values must be in range 0255)
	PPMWriter::PPMWriter(width, height, pixelbuffer, outputFile);
	auto end_time = std::chrono::high_resolution_clock::now();

	std::cout<<"Total elapsed time: "<<std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()/ 1000000.0)<<std::endl;
	std::cout<<"Render elapsed time: "<<std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_rend).count()/ 1000000.0)<<std::endl;

	delete pixelbuffer;
}


