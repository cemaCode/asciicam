#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include<string>
#include <fstream>

using namespace cv;
using namespace std;

const string short_ascii_grayscale = "@%#*+=-:. ";
/// <summary>
/// Writes content to file 
/// </summary>
/// <param name="P_textToWrite"></param>
/// <param name="P_fileNamePath"></param>
void writeInFile(string P_textToWrite, string P_fileNamePath = "result.txt")
{
	ofstream fileToWriteTo(P_fileNamePath);
	fileToWriteTo << P_textToWrite;
	fileToWriteTo.close();
}

/// <summary>
	/// Convert to each pixel value to ascii 
	/// </summary>
	/// <param name="P_imageToConvert"></param>
	/// <param name="P_asciiGrayscaleToUse"></param>
	/// <param name="printOut"></param>
	/// <returns></returns>

string convertToAscii(Mat& P_imageToConvert, string P_asciiGrayscaleToUse = short_ascii_grayscale, bool printOut = 1)
{
	
	string convertedImage = "";
	//We iterate throug every row and column
	for (int i = 0; i < P_imageToConvert.rows; i += 2)
	{
		for (int j = 0; j < P_imageToConvert.cols; j++)
		{
			//We assign an ascii char for each pixel value 
			convertedImage += P_asciiGrayscaleToUse[P_imageToConvert.at<uchar>(i, j)
				/ (255 / P_asciiGrayscaleToUse.size())];
		}
		//New line for each row
		convertedImage += '\n';
	}
	if (printOut)
	{
		cout << convertedImage << endl;
	}
	return convertedImage;
}
/// <summary>
/// Rescale and convert to grayscale
/// </summary>
/// <param name="P_orignalInput"></param>
void imageProcessing(Mat& P_orignalInput)
{
	// Rescale and convert to grayscale before ascii conversion 
	resize(P_orignalInput, P_orignalInput, Size(216, 144));
	cvtColor(P_orignalInput, P_orignalInput, COLOR_BGR2GRAY);
}

enum COLOR { BLACK, WHITE, GREEN };
/// <summary>
/// Deals with text and gives frame with result 
/// </summary>
/// <param name="P_textToPrint"></param>
/// <param name="P_bgColor"></param>
/// <param name="P_txtColor"></param>
/// <returns>Returns frame with ascii art</returns>
Mat TextWindow(string P_textToPrint, COLOR P_bgColor = BLACK, COLOR P_txtColor = WHITE)
{
	//Select Background color 
	Scalar background_color;
	switch (P_bgColor)
	{
	case BLACK:
		background_color = Scalar(0, 0, 0);
		break;
	case WHITE:
		background_color = Scalar(255, 255, 255);
		break;
	case GREEN:
		background_color = Scalar(0, 255, 0);
		break;
	default:
		break;
	}

	//Select text color 
	Scalar text_color;
	switch (P_txtColor)
	{
	case BLACK:
		text_color = Scalar(0, 0, 0);
		break;
	case WHITE:
		text_color = Scalar(255, 255, 255);
		break;
	case GREEN:
		text_color = Scalar(0, 255, 0);
		break;
	default:
		break;
	}

	//Create background 
	Mat bg = Mat(Size(1080, 720), CV_8UC3, background_color);

	//Sliting input text by line 
		//	Because putText cant' deal with '\n'
	stringstream ss(P_textToPrint);
	string first_line;
	int i = 1;

	// For each line in input
	while (getline(ss, first_line, '\n'))
	{
		double scale = 0.4; //Text size  
		int font = FONT_HERSHEY_PLAIN;

		Size text_size = getTextSize(first_line, font, scale, 1, 0); // Gets width, height of line 
		float biggest_width = getTextSize("@", font, scale, 1, 0).width; //Gets width off largest char 
																			//from ascii grayscale
		//For each character in a line
		for (int x = 0; x < first_line.length(); x++)
		{
			string current_char_in_string = string(1, first_line.at(x));
			//We place the char with specific x pos to correct for different char width
			putText(bg, current_char_in_string, Point(x * 5,
				(0 + text_size.height * i)), font, scale, text_color);
		}
		i += 2; // +2 b/c better for line spacing 
	}

	return bg;
}



int main()
{
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cerr << "UNABLE TO OPEN WEBCAM!" << endl;
		return -1;
	}

	bool run = true;
	while (run)
	{
		Mat frame;

		Mat display;
		string result;
		capture.read(frame);
		if (frame.empty()) {
			cerr << "ERROR Frame is blank" << endl;
			return -1;
		}

		imageProcessing(frame);
		result = convertToAscii(frame, short_ascii_grayscale, true);
		display = TextWindow(result, BLACK, GREEN);
		
		imshow("ASCIICAM", display);
		if (waitKey(5) >= 0)
			run = false;
		run = false;
	}
	return 0;
}
