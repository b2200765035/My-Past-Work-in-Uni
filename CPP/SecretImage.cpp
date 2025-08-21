#include "SecretImage.h"


// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage& image) {
    // TODO: Your code goes here.

    height = image.get_height();
    width = image.get_width();
    
    // 1. Dynamically allocate the memory for the upper and lower triangular matrices.
    int n = width;

    upper_triangular = new int[n * (n + 1) / 2];  // Upper triangle
    lower_triangular = new int[n * (n - 1) / 2];  // Lower triangle

    // 2. Fill both matrices with the pixels from the GrayscaleImage.
    int upper_index = 0; // Iterating variable
    int lower_index = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int pixel = image.get_pixel(i, j);

            if (j >= i) {
                // Upper triangle
                // 1,1 1,2 1,3 .... 5,5 5,6 etc....
                upper_triangular[upper_index++] = pixel;
            } else {
                // Lower triangle
                // 2,1 3,1 3,2 ... etc...
                lower_triangular[lower_index++] = pixel;
            }
        }
    }
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int * upper, int * lower) {
    // TODO: Your code goes here.

    height = h;
    width = w;

    // Since file reading part should dynamically allocate upper and lower matrices.
    // You should simply copy the parameters to instance variables.
    int n = width;
    
    int upper_limit = n * (n + 1) / 2;
    int lower_limit = n * (n - 1) / 2;

    upper_triangular = new int[upper_limit];  // Upper triangle
    lower_triangular = new int[lower_limit];  // Lower triangle

    for(int i = 0; i < upper_limit; ++i){
        upper_triangular[i] = upper[i];
    }

    for(int i = 0; i < lower_limit; ++i){
        lower_triangular[i] = lower[i];
    }
}


// Destructor: free the arrays
SecretImage::~SecretImage() {
    // TODO: Your code goes here.

    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.
    delete[] upper_triangular;
    delete[] lower_triangular;
}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const {
    GrayscaleImage image(width, height);

    // TODO: Your code goes here.
    int upper_index = 0;  // Upper triangle
    int lower_index = 0;  // Lower triangle

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i <= j) {
                // Upper triangle
                image.set_pixel(i, j, upper_triangular[upper_index]);
                upper_index++;
            } else {
                // Lower triangle
                image.set_pixel(i, j, lower_triangular[lower_index]);
                lower_index++;
            }
        }
    }

    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage& image) {
    // TODO: Your code goes here.

    // Update the lower and upper triangular matrices 
    // based on the GrayscaleImage given as the parameter.
    int upper_index = 0;  // Upper triangle
    int lower_index = 0;  // Lower triangle

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i <= j) {
                // Upper triangle
                upper_triangular[upper_index] = image.get_pixel(i, j);
                upper_index++;
            } else {
                // Lower triangle
                lower_triangular[lower_index] = image.get_pixel(i, j);
                lower_index++;
            }
        }
    }
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string& filename) {
    // TODO: Your code goes here.

    std::ofstream outFile(filename);

    // 1. Write width and height on the first line, separated by a single space.
    outFile << width << " " << height << std::endl;
    int n = width;

    // 2. Write the upper_triangular array to the second line.
    // Ensure that the elements are space-separated. 
    // If there are 15 elements, write them as: "element1 element2 ... element15"
    for (int i = 0; i < (n * (n + 1)) / 2; ++i) {
        // Upper triangle
        outFile << upper_triangular[i];
        if (i < (n * (n + 1)) / 2 - 1) {
            outFile << " ";  // Add space
        }
    }
    outFile << std::endl;  // New line

    // 3. Write the lower_triangular array to the third line in a similar manner
    // as the second line.
    for (int i = 0; i < (n * (n - 1)) / 2; ++i) {
        // Lower triangle
        outFile << upper_triangular[i];
        if (i < (n * (n - 1)) / 2 - 1) {
            outFile << " ";  // Add space
        }
    }

    outFile.close();
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string& filename) {
    // TODO: Your code goes here.

    std::ifstream inFile(filename);

    // 1. Open the file and read width and height from the first line, separated by a space.
    int w, h;
    inFile >> w >> h;

    // 2. Calculate the sizes of the upper and lower triangular arrays.
    int upper_size = (w * (w + 1)) / 2;  // Upper triangle
    int lower_size = (w * (w - 1)) / 2;  // Lower triangle

    // 3. Allocate memory for both arrays.
    int* upper = new int[upper_size];
    int* lower = new int[lower_size];

    // 4. Read the upper_triangular array from the second line, space-separated.
    for (int i = 0; i < upper_size; ++i) {
        inFile >> upper[i];
    }

    // 5. Read the lower_triangular array from the third line, space-separated.
    for (int i = 0; i < lower_size; ++i) {
        inFile >> lower[i];
    }

    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.
    inFile.close();
    SecretImage secret_image(w, h, upper, lower);
    return secret_image;
}

// Returns a pointer to the upper triangular part of the secret image.
int * SecretImage::get_upper_triangular() const {
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int * SecretImage::get_lower_triangular() const {
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const {
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const {
    return height;
}
