#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {
    // TODO: Your code goes here.

    int width = image.get_width();
    int height = image.get_height();
    int halfKernel = kernelSize / 2; //This gives 1 when kernelSize is 3. I use this to limit my searches to -1,0,1 

    // 1. Copy the original image for reference.
    GrayscaleImage reference = GrayscaleImage(image);

    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int sum = 0;
            int divider = kernelSize * kernelSize;

            for (int i = -halfKernel; i <= halfKernel; ++i) {
                for (int j = -halfKernel; j <= halfKernel; ++j) {
                    int currentRow = row + i;
                    int currentCol = col + j;

                    // This is so that I don't try to acsess out of bounds pixel
                    if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width) {
                        sum += reference.get_pixel(currentRow, currentCol);
                    }
                }
            }
            int meanValue = sum / divider;

            // 3. Update each pixel with the computed mean.
            image.set_pixel(row, col, meanValue);
        }
    }
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {
    // TODO: Your code goes here.

    int width = image.get_width();
    int height = image.get_height();
    int halfKernel = kernelSize / 2; //This gives 1 when kernelSize is 3. I use this to limit my searches to -1,0,1
    GrayscaleImage reference = GrayscaleImage(image);

    // 1. Create a Gaussian kernel based on the given sigma value.
    double** kernel = new double*[kernelSize];
    double sum = 0.0;
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i] = new double[kernelSize];
        for (int j = 0; j < kernelSize; ++j) {
            int x = i - halfKernel;
            int y = j - halfKernel;
            kernel[i][j] = std::exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += kernel[i][j];
        }
    }

    // 2. Normalize the kernel to ensure it sums to 1.
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }

    // 3. For each pixel, compute the weighted sum using the kernel.
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            double weightedSum = 0.0;

            // Convolve with kernel
            for (int i = -halfKernel; i <= halfKernel; ++i) {
                for (int j = -halfKernel; j <= halfKernel; ++j) {
                    int neighborRow = row + i;
                    int neighborCol = col + j;

                    // Check if the neighbor is within bounds
                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width) {
                        weightedSum += reference.get_pixel(neighborRow, neighborCol) * kernel[i + halfKernel][j + halfKernel];
                    }
                }
            }

            // 4. Update the pixel values with the smoothed results.
            image.set_pixel(row, col, static_cast<int>(weightedSum));
        }
    }

    // Deleting kernel for memory reasons
    for (int i = 0; i < kernelSize; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    // TODO: Your code goes here.

    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    GrayscaleImage blurredImage = image;
    apply_gaussian_smoothing(blurredImage, kernelSize);

    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    for (int i = 0; i < image.get_height(); ++i) {
        for (int j = 0; j < image.get_width(); ++j) {
            int originalPixel = image.get_pixel(i, j);
            int blurredPixel = blurredImage.get_pixel(i, j);
            int sharpenedPixel = originalPixel + amount * (originalPixel - blurredPixel);

            // 3. Clip values to ensure they are within a valid range [0-255].
            if (sharpenedPixel < 0) sharpenedPixel = 0;
            if (sharpenedPixel > 255) sharpenedPixel = 255;

            image.set_pixel(i, j, sharpenedPixel);
        }
    }
}