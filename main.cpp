#include <fstream>
#include <vector>
#include <cmath>

#include <stdlib.h>

#include <vect.h>
#include <ray.h>
#include <camera.h>
#include <color.h>
#include <source.h>
#include <light.h>
#include <object.h>
#include <sphere.h>
#include <plane.h>

struct RGBType {
	double r;
	double g;
	double b;
};

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data)
{
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;

	int ppm = dpi*39;
	
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>>8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w>>8);
	bmpinfoheader[6] = (unsigned char)(w>>16);
	bmpinfoheader[7] = (unsigned char)(w>>24);
	
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);
	
	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);
	
	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);
	
	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);
	
	f = fopen(filename, "wb");
	
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	
	for (int i = 0; i < k; i++) {
		double red = (data[i].r)*255;
		double green = (data[i].g)*255;
		double blue = (data[i].b)*255;
		
		unsigned char color[3] = {(int)floor(blue), (int)floor(green), (int)floor(red)};
		
		fwrite(color,1,3,f);
	}
	
	fclose(f);
}

int winningObjectIndex(std::vector<double> object_intersections)
{
	// return the index of the winning intersection
	int index_of_minimum_value;
	
	// prevent unnessary calculations
	if (object_intersections.size() == 0) {
		//————————No intersections?—————————
		//⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
		//⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
		//⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
		//⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀
		//⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
		//⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
		//⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		//⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		//——————————————————————————————————
		return -1;
	} else if (object_intersections.size() == 1) {
		if (object_intersections.at(0) > 0) {
			// if that intersection is greater than zero then its our index of
			// minimum value
			return 0;
		} else {
			// otherwise the only intersection value is negative
			return -1;
		}
	} else {
		// more than one intersection
		// find the maximum value
		
		double max = 0;
		for (int i = 0; i < object_intersections.size(); i++) {
			if (max < object_intersections.at(i)) {
				max = object_intersections.at(i);
			}
		}
		
		// then starting from the maximum value find the minimum
		// positive value
		if (max > 0) {
			// we only want positive intersections
			for (int index = 0; index < object_intersections.size(); index++) {
				if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
					max = object_intersections.at(index);
					index_of_minimum_value = index;
				}
			}
			
			return index_of_minimum_value;
		} else {
			// all the intersections were negative
			return -1;
		}
	}
}

Color getColorAt(Vect intersection_position, Vect intersecting_ray_direction, std::vector<Object*> scene_objects, int index_of_winning_object, std::vector<Source*> light_sources, double accuracy)
{
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
	
	if (winning_object_color.getColorSpecial() == 2) {
		// checkered/tile floor pattern
		int square = floor(intersection_position.getVectX()) + floor(intersection_position.getVectZ());
		
		if ((square % 2) == 0) {
			// black tile
			winning_object_color.setColorRgbs(0, 0, 0);
		} else {
			// white tile
			winning_object_color.setColorRgbs(1, 1, 1);
		}
	}
	
	Color final_color = winning_object_color.colorScalar(0.2);
	
	if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
		// reflection from objects with specular intensity
		Vect scalar1 = winning_object_normal.vectMult(winning_object_normal.dotProduct(intersecting_ray_direction.negative()));
		Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
		Vect scalar2 = add1.vectMult(2);
		Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
		Vect reflection_direction = add2.normalize();
		
		Ray reflection_ray (intersection_position, reflection_direction);
		
		// determine what the ray intersects with first
		std::vector<double> reflection_intersections;
		
		for (int reflection_index = 0; reflection_index < 2; reflection_index++) {
			reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
		}
		
		int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);
		
		if (index_of_winning_object_with_reflection != -1) {
			// reflection ray missed everthing else
			if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
				// determine the position and direction at the point of intersection with the reflection ray
				// the ray only affects the color if it reflected off something
				
				Vect reflection_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections.at(index_of_winning_object_with_reflection)));
				Vect reflection_intersection_ray_direction = reflection_direction;
				
				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy);
				
				final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(winning_object_color.getColorSpecial()));
			}
		}
	}
	
	for (int light_index = 0; light_index < light_sources.size(); light_index++) {
		Vect light_direction = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();
		
		float cosine_angle = winning_object_normal.dotProduct(light_direction);
		
		if (cosine_angle > 0) {
			Ray shadow_ray(intersection_position, light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize());
			
			std::vector<double> secondary_intersections;
			
			for (int object_index = 0; object_index < 2; object_index++) {
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
			}

			final_color = final_color.colorAdd(winning_object_color.colorMultiply(light_sources.at(light_index)->getLightColor()).colorScalar(cosine_angle));
			
			// special [0-1]
			Vect scalar1 = winning_object_normal.vectMult(winning_object_normal.dotProduct(intersecting_ray_direction.negative()));
			Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
			Vect scalar2 = add1.vectMult(2);
			Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
			Vect reflection_direction = add2.normalize();
			
			double specular = reflection_direction.dotProduct(light_direction);
			if (specular > 0) {
				specular = pow(specular, 10);
				final_color = final_color.colorAdd(light_sources.at(light_index)->getLightColor().colorScalar(specular*winning_object_color.getColorSpecial()));
			}
		}
	}
	
	return final_color.clip();
}

int main(int argc, char *argv[])
{
	int dpi = 900;
	int width = 3840;
	int height = 2160;
	int n = width * height;
	RGBType *pixels = new RGBType[n];

	double aspectratio = (double)width/(double)height;
	double accuracy = 0.00000001;

	Vect O(0,0,0);
	Vect X(1,0,0);
	Vect Y(0,1,0);
	Vect Z(0,0,1);
	
	Vect new_sphere_location(1.75, -0.25, 0);
	
	Vect campos(3, 1.5, -4);
	Vect look_at(0, 0, 0);

	Vect diff_btw(campos.getVectX() - look_at.getVectX(), campos.getVectY() - look_at.getVectY(), campos.getVectZ() - look_at.getVectZ());
	
	Vect camdir = diff_btw.negative().normalize();
	Vect camright = Y.crossProduct(camdir).normalize();
	Vect camdown = camright.crossProduct(camdir);
	Camera scene_cam(campos, camdir, camright, camdown);
	
	Color white_light(1.0, 1.0, 1.0, 0);
	Color pretty_green(0.5, 1.0, 0.5, 0.3);
	Color maroon(0.5, 0.25, 0.25, 0);
	Color tile_floor(1, 1, 1, 2);
	Color gray(0.5, 0.5, 0.5, 0);
	Color black(0.0, 0.0, 0.0, 0);
	
	Vect light_position(-7,10,-10);
	Light scene_light(light_position, white_light);

	std::vector<Source *> light_sources;
	light_sources.push_back(dynamic_cast<Source*>(&scene_light));
	
	// scene objects
	Sphere scene_sphere(O, 1, pretty_green);
	Plane scene_plane(Y, -1, tile_floor);

	std::vector<Object *> scene_objects;
	scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
	scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));
	
	int thisone;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y*width + x;

			Vect cam_ray_origin = scene_cam.getCameraPosition();
			Vect cam_ray_direction;

			// create the ray from the camera to this pixel
			// no anti-aliasing
			if (width > height) {
				// the image is wider than it is tall
				cam_ray_direction = camdir.vectAdd(camright.vectMult(((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2)-0.5).vectAdd(camdown.vectMult(((height-y)+0.5)/height-0.5))).normalize();
			} else if (width < height) {
				// the imager is taller than it is wide
				cam_ray_direction = camdir.vectAdd(camright.vectMult((x+0.5)/width-0.5).vectAdd(camdown.vectMult((((height-y)+0.5)/height)/aspectratio - (((height-width)/(double)width)/2)-0.5))).normalize();
			} else {
				// the image is square
				cam_ray_direction = camdir.vectAdd(camright.vectMult((x+0.5)/width-0.5).vectAdd(camdown.vectMult(((height-y)+0.5)/height-0.5))).normalize();
			}
			
			Ray cam_ray(cam_ray_origin, cam_ray_direction);

			std::vector<double> intersections;

			for (int index = 0; index < 2; index++) {
				intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
			}

			int index_of_winning_object = winningObjectIndex(intersections);

			if (index_of_winning_object == -1) {
				// set the backgroung black
				pixels[thisone].r = 0;
				pixels[thisone].g = 0;
				pixels[thisone].b = 0;
			} else {
				// index coresponds to an object in our scene
				if (intersections.at(index_of_winning_object) > accuracy) {
					// determine the position and direction std::vectors at the point of intersection

					Vect intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
					Vect intersecting_ray_direction = cam_ray_direction;

					Color intersection_color = getColorAt(intersection_position, intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy);

					pixels[thisone].r = intersection_color.getColorRed();
					pixels[thisone].g = intersection_color.getColorGreen();
					pixels[thisone].b = intersection_color.getColorBlue();
				}
			}
		}
	}

	savebmp("scene.bmp",width,height,dpi,pixels);

	delete[] pixels;
	return 0;
}