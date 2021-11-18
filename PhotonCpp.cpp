// PhotonCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"


std::pair<std::string, PhotonLayer> png2layer(const std::string & bufferPng)
{
	char* img = nullptr;
	int w = 0;
	int h = 0;
	int n = 0;
	img = (char*)stbi_load_from_memory((unsigned char*)bufferPng.data(), bufferPng.length(), &w, &h, &n, 4);
	PhotonLayer res(w, h);

	if (!img)
		return {"Invalid PNG file format", res};

	if (w != 1440 || h != 2560)
		return { "Invalid PNG image size: (" + std::to_string(w) + "x" + std::to_string(h) + " instead of 1440x2560)", res };

	for (int j = 0; j < h; j++)
		for (int i = 0; i < w; i++)
		{
			int pos = ((w * j) + i) * 4;
			bool present = (img[pos + 3] != 0 /* not alpha transparent */) && (img[pos] == 0 /* probably black */);
			if (!present)
				res.supported(i, j);
		}

	stbi_image_free(img);
	return { "", res };
}

std::string getModel()
{
	const unsigned char gz[] = { 
120, 94, 147, 100, 248, 43, 196, 196, 192, 192, 80, 45, 210, 225, 212, 250,
250, 163, 19, 3, 131, 152, 51, 3, 18, 56, 123, 198, 199, 150, 129, 97,
129, 35, 3, 3, 11, 80, 220, 193, 129, 3, 40, 183, 128, 21, 72, 112,
49, 48, 20, 0, 169, 43, 64, 205, 204, 64, 186, 133, 145, 129, 225, 25,
144, 1, 164, 24, 102, 0, 197, 108, 128, 98, 32, 246, 127, 134, 255, 200,
198, 49, 232, 2, 121, 32, 60, 1, 72, 127, 97, 192, 4, 58, 201, 219,
140, 252, 163, 11, 189, 57, 13, 78, 71, 233, 36, 43, 24, 108, 81, 230,
2, 179, 228, 13, 206, 121, 109, 81, 230, 52, 184, 32, 5, 18, 13, 244,
6, 177, 59, 4, 33, 42, 64, 162, 32, 182, 188, 1, 68, 252, 130, 20,
50, 175, 67, 16, 194, 131, 232, 238, 16, 228, 50, 210, 73, 150, 67, 82,
9, 225, 131, 236, 1, 169, 4, 241, 100, 145, 100, 33, 234, 97, 34, 190,
82, 32, 53, 93, 94, 58, 201, 178, 96, 151, 173, 16, 100, 50, 0, 241,
100, 12, 252, 163, 13, 193, 174, 131, 137, 200, 26, 156, 137, 234, 177, 210,
145, 226, 48, 56, 37, 8, 211, 35, 111, 208, 227, 165, 35, 197, 9, 20,
1, 233, 81, 52, 120, 19, 197, 105, 160, 147, 28, 110, 36, 15, 12, 6,
16, 94, 2, 12, 48, 236, 97, 194, 98, 136, 8, 19, 33, 120, 152, 8,
34, 133, 137, 144, 1, 34, 76, 64, 42, 96, 97, 34, 136, 18, 38, 130,
112, 85, 160, 48, 17, 52, 64, 14, 19, 1, 180, 48, 17, 48, 64, 14,
19, 126, 140, 48, 129, 137, 32, 194, 132, 31, 37, 76, 248, 48, 194, 132,
31, 75, 152, 8, 162, 132, 137, 48, 52, 76, 14, 26, 48, 48, 60, 112,
96, 96, 104, 2, 166, 199, 5, 80, 90, 204, 217, 108, 71, 190, 89, 203,
141, 102, 179, 26, 197, 103, 198, 12, 12, 14, 14, 32, 204, 193, 128, 11,
64, 210, 171, 3, 48, 77, 154, 21, 99, 170, 129, 164, 107, 136, 154, 178,
50, 6, 6, 236, 106, 206, 216, 194, 210, 253, 154, 151, 216, 213, 212, 142,
130, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129,
209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209,
16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16,
24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24,
13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13,
129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129,
209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209,
16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 129, 209, 16,
24, 13, 129, 209, 16, 24, 13, 129, 209, 16, 24, 13, 1, 66, 33, 144,
209, 140, 164, 194, 174, 121, 52, 192, 70, 67, 96, 52, 4, 70, 67, 96,
52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52,
4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4,
70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70,
67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67,
96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96,
52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52,
4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4,
70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70, 67, 96, 52, 4, 70,
67, 96, 52, 4, 8, 134, 64, 250, 104, 24, 141, 134, 192, 104, 8, 140,
134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134,
192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192,
104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104,
8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8,
140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140,
134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134,
192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192,
104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104,
8, 140, 134, 192, 104, 8, 16, 12, 129, 204, 38, 36, 37, 246, 77, 163,
33, 54, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33,
48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48,
26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26,
2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2,
163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163,
33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33,
48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48,
26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26,
2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 64, 48, 4,
70, 111, 205, 28, 77, 36, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2,
163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163,
33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33,
48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48,
26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26,
2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2,
163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163,
33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33,
48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 48, 26, 2, 163, 33, 64,
56, 4, 178, 26, 145, 212, 56, 52, 142, 6, 217, 104, 8, 140, 134, 192,
104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104,
8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8,
140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140,
134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134,
192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192,
104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104,
8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8,
140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140, 134, 192, 104, 8, 140,
134, 192, 104, 8, 140, 134, 0, 193, 16, 72, 7, 0, 143, 56, 126, 118
	};

	std::string res;
	res.resize(100*1024);

	int len = stbi_zlib_decode_buffer(&res[0], res.length(), (const char*)gz, sizeof gz);

	res.resize(len);
	return res;
}

int main(int argc, char * argv[])
{
	if (argc != 3 && argc != 4)
	{
		std::cerr << "\nUsage: PngToPhoton <input-1440x2560.png or directory> <output.photon> <layer_thickness?>\n"
		"To read data from STDIN use '-' as filename.\n"
		"To read from a directory pass it in place of the input image.\n"
		"To write data to STDOUT use '-' as filename.\n\n"
		"White and transparent areas of the image are treated as voids.\n"
		"Check with Photon File Validator after conversion. Use output at your own risk.\n";
		return -1;
	}

#ifdef WIN32
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stdin), _O_BINARY);
#endif // WIN32

	std::string bufferModel = getModel();

	PhotonFileHeader photonFileHeader(bufferModel);
	
	// load png
	std::map<std::string, std::string> bufferPngs;
	struct stat s;

	if (std::string("-") == argv[1])
	{
		std::string tmp(std::istreambuf_iterator<char>(std::cin), {});
		bufferPngs[argv[1]] = std::move(tmp);
	}
	else if (stat(argv[1], &s) == 0)
	{
		std::string directoryPath(argv[1]);
		if (s.st_mode & S_IFDIR)
		{
			DIR *dp;
			struct dirent *ep;     
			dp = opendir(argv[1]);

			if (dp != NULL)
			{
				while (ep = readdir(dp)) {
					if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
						continue;
					std::string strPath(directoryPath);
					strPath += "/";
					strPath += ep->d_name;
					std::ifstream ifPng(strPath, std::ios_base::binary);

					if (ifPng.fail())
					{
						std::cerr << "Error opening input file.\n";
						std::cerr << strPath << '\n';
						return -1;
					}

					ifPng.seekg(0, std::ios::end);
					std::streamoff size = 0;
					size = ifPng.tellg();
					std::string bufferPng;
					bufferPng.resize((unsigned int)size);
					ifPng.seekg(0);
					ifPng.read(&bufferPng[0], size);
					ifPng.close();
					bufferPngs[strPath] = bufferPng;
				}
				closedir(dp);
			}
			else
				std::cerr << "Couldn't open directory " << argv[1] << std::endl;
		}
		else if (s.st_mode & S_IFREG)
		{
			std::ifstream ifPng(argv[1], std::ios_base::binary);

			if (ifPng.fail())
			{
				std::cerr << "Error opening input file.\n";
				return -1;
			}

			ifPng.seekg(0, std::ios::end);
			std::streamoff size = 0;
			size = ifPng.tellg();
			std::string bufferPng;
			bufferPng.resize((unsigned int)size);
			ifPng.seekg(0);
			ifPng.read(&bufferPng[0], size);
			ifPng.close();
			bufferPngs[argv[1]] = bufferPng;
		}
		else
		{
			std::cerr << "Not a directory nor a file. \n";
		}
	}
	else
	{
		std::cerr << "File not found. \n";
		return -1;
	}


	int antiAliasLevel = 1;
	if (photonFileHeader.getVersion() > 1) {
		antiAliasLevel = photonFileHeader.getAntiAliasingLevel();
	}

	photonFileHeader.setNumberOfLayers(bufferPngs.size());
	PhotonFilePreview previewOne(photonFileHeader.getPreviewOneOffsetAddress(), bufferModel);
	PhotonFilePreview previewTwo(photonFileHeader.getPreviewTwoOffsetAddress(), bufferModel);
	
	PhotonFilePrintParameters photonFilePrintParameters;
	if (photonFileHeader.getVersion() > 1) 
	{
		PhotonFilePrintParameters dummy(photonFileHeader.getPrintParametersOffsetAddress(), bufferModel);
		photonFilePrintParameters = std::move(dummy);
	}

	int margin = 0;
	float layerThickness = (argc == 4 ? atof(argv[3]) : 0.02f);
	std::vector<PhotonFileLayer> layers = PhotonFileLayer::readLayers(photonFileHeader, bufferModel, margin, layerThickness);
	int i = 0;

	//std::sort(bufferPngs.begin(), bufferPngs.end());

	for (auto bufferPng : bufferPngs) {
		std::pair<std::string, PhotonLayer> rle = png2layer(bufferPng.second);
		if (!rle.first.empty())
		{
			std::cerr << rle.first << "\n";
			return -1;
		}
		PhotonLayer & layerPng = rle.second;

		PhotonFileLayer & layer = layers.at(i++);
		layer.saveLayer(layerPng);
	}

	// writing is here:
	int headerPos = 0;
	int previewOnePos = headerPos + photonFileHeader.getByteSize();
	int previewTwoPos = previewOnePos + previewOne.getByteSize();
	int layerDefinitionPos = previewTwoPos + previewTwo.getByteSize();

	int parametersPos = 0;
	if (photonFileHeader.getVersion() > 1) {
		parametersPos = layerDefinitionPos;
		layerDefinitionPos = parametersPos + photonFilePrintParameters.getByteSize();
	}

	int dataPosition = layerDefinitionPos + (PhotonFileLayer::getByteSize() * photonFileHeader.getNumberOfLayers() * antiAliasLevel);


	std::ofstream ofs;
	if (std::string("-") != argv[2])
	{
		ofs.open(argv[2], std::ios_base::binary);
		if (ofs.fail())
		{
			std::cerr << "Error opening output file.\n";
			return -1;
		}
	}

	PhotonOutputStream os( std::string("-") != argv[2] ? ofs : std::cout);
	photonFileHeader.save(os, previewOnePos, previewTwoPos, layerDefinitionPos, parametersPos);
	previewOne.save(os, previewOnePos);
	previewTwo.save(os, previewTwoPos);

	if (photonFileHeader.getVersion() > 1) {
		photonFilePrintParameters.save(os);
	}

	// Optimize order for speed read on photon
	for (int i = 0; i < photonFileHeader.getNumberOfLayers(); i++) {
		PhotonFileLayer & layer = layers.at(i);
		dataPosition = layer.savePos(dataPosition);
	}

	// Order for backward compatibility with photon/cbddlp version 1
	for (int i = 0; i < photonFileHeader.getNumberOfLayers(); i++) {
		layers.at(i).save(os);
	}

	// Optimize order for speed read on photon
	for (int i = 0; i < photonFileHeader.getNumberOfLayers(); i++) {
		PhotonFileLayer & layer = layers.at(i);
		layer.saveData(os);
	}
	ofs.close();

	return 0;
}
