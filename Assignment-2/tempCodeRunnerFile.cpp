    # include <iostream>
    # include <string>
    # include <fstream>
    using namespace std;

    class Image {
        private:
            int width;
            int height;
            int maxGreyVal;
            int** arrayOfPixels;
            string magic;
        public:
            // default constructor --> since data is to be read
            // from file and not gonna be input
            Image ();
            // destructor
            ~Image ();
            //functions to be implemented
            void readImage (string);    // reads from file
            void saveImage (string);    // reads into file
            void changeBrightness (int);    //-255 to +255
            void flipImage (string);  // requires direction
            void negate ();
            void medianFilter ();
            void combineImages (Image);  // requires another image
            void applyFilter (); //i've used blur filter as it is similar to median filter

    };

    // constructor
    Image :: Image ()   {
        width = 0;
        height = 0;
        maxGreyVal = 255;
        arrayOfPixels = nullptr;
    }

    // destructor
    Image :: ~Image ()  {
        for (int i = 0; i < height; i++)    {
            delete[] *(arrayOfPixels + i);
        }
        delete[] arrayOfPixels;
    }
    //Save Image Funcion
    void Image :: readImage (string sample)   {
        ifstream fin (sample);
        if (!fin) {
            cout << "File not found" << endl;
            return;
        }

        fin >> magic;
        fin >> width;
        fin >> height;
        fin >> maxGreyVal;

        arrayOfPixels = new int* [height];

        // input pixel data
        for (int i = 0; i < height; i++)    {
            *(arrayOfPixels + i) = new int [width];
            for (int j = 0; j < width; j++)     {
                fin >> *(*(arrayOfPixels + i) + j);
            }
        }
        return;
    }

    // Read Image Function
    void Image :: saveImage (string sample)  {
        ofstream fout (sample);
        if (!fout) {
            cout << "File not found" << endl;
            return;
        }

        fout << magic << endl;
        fout << width << " " << height << endl;
        fout << maxGreyVal << endl;

        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                fout << *(*(arrayOfPixels + i) + j) << " ";
            }
            fout << endl;
        }

        return;
    }

    // Brightness Function
    void Image :: changeBrightness(int pixelChange) {

        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                if ((*(*(arrayOfPixels + i) + j) + pixelChange) > 255)  *(*(arrayOfPixels + i) + j) = 255;
                else if ((*(*(arrayOfPixels + i) + j) + pixelChange) < 0)  *(*(arrayOfPixels + i) + j) = 0;
                else *(*(arrayOfPixels + i) + j) += pixelChange;
            }
        }

        return;
    }

    // Flip Image Function
    void Image :: flipImage (string direction)  {

        if (direction == "horizontal" || direction == "Horizontal") {
            // for horizontal, fix rows (height) and reverse cols (width)
            // untill middle col (width / 2) is reached
            for (int i = 0; i < height; i++)    {
                for (int j = 0; j < width / 2; j++) {
                    int temp = *(*(arrayOfPixels + i) + j);
                    *(*(arrayOfPixels + i) + j) = *(*(arrayOfPixels + i) + (width - 1 - j));
                    *(*(arrayOfPixels + i) + (width - 1 - j)) = temp;
                }
            }
        }
        else if (direction == "vertical" || direction == "Vertical")    {
            // for horizontal, fix cols (width) and reverse rows (height)
            // untill middle row (height / 2) is reached
            for (int i = 0; i < height / 2; i++)    {
                for (int j = 0; j < width; j++) {
                    int temp = *(*(arrayOfPixels + i) + j);
                    *(*(arrayOfPixels + i) + j) = *(*(arrayOfPixels + (height - 1 -i)) + j);
                    *(*(arrayOfPixels + (height - 1 - i)) + j) = temp;
                }
            }
        }
        else cout << "Invalid Operation Called. Try first CAPS or all SMALL" << endl;

        return;
    }

    // Negate Function
    void Image :: negate()  {

        // 255 - current pixel = new pixel
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                *(*(arrayOfPixels + i) + j) = 255 - *(*(arrayOfPixels + i) + j);
            }
        }

        return;
    }

    // Combine Images Function
    void Image :: combineImages (Image other)  {
        if (height != other.height) {
            cout << "Heights don't match!" << endl;
            return;
        }
        // calculate new width (here width is this->width)
        int newWidth = width + other.width;

        // new array for larger image
        int** newArray = new int* [height];
        for (int i = 0; i < height; i++)    {
            *(newArray + i) = new int [newWidth];
        }

        // copy first image
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                *(*(newArray + i) + j) = *(*(arrayOfPixels + i) + j);
            }
        }

        // copy second image
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < other.width; j++)   {
                *(*(newArray + i) + (width + j)) = *(*(other.arrayOfPixels + i) + j);
            }
        }

        // delete old array
        for (int i = 0; i < height; i++)    {
            delete[] *(arrayOfPixels + i);
        }
        delete[] arrayOfPixels;

        // point it to new array
        arrayOfPixels = newArray;
        width = newWidth;

        return;
    }

    //Median Filter Function
    void Image :: medianFilter()    {
        
        // create a copy so org is not changed
        int** copy = new int* [height];
        for (int i = 0; i < height; i++)    {
            *(copy + i) = new int [width];
            for (int j = 0; j < width; j++) {
                *(*(copy + i) + j) = *(*(arrayOfPixels + i) + j);
            }
        }

        // note that there cannot be nine neighbours for any cell
        // on the boundary row or boundary col, so ignore them
        for (int i = 1; i < height - 1; i++)    {
            for (int j = 1; j < width - 1; j++) {
                // arry for all neighbours
                int size = 9;
                int arr[9], k = 0; // k is used to traverse arr
                
                // now in order to collect the neighbours we use
                // -1 0 and 1 as the neighbours are one prev, one
                // at same pos and one next

                for (int ni = -1; ni <= 1; ni++)    {
                    for (int nj = -1; nj <= 1; nj++)    {
                        *(arr + (k++)) = *(*(copy + (i + ni)) + (j + nj));
                    }
                }

                // sort the array arr
                for (int x = 0; x < size - 1; x++)  {
                    for (int y = 0; y < size - x - 1; y++)  {
                        if (*(arr + y) > *(arr + (y + 1)))  {
                            int temp = *(arr + y);
                            *(arr + y) = *(arr + (y + 1));
                            *(arr + (y + 1)) = temp;
                        }
                    }
                }

                // now finally replace the median value wchich is 4
                *(*(arrayOfPixels + i) + j) = *(arr + 4); // here we change the value of 
                // org array and hence for future the neighbours would change, so we made a copy

                
            }
        } 
        // delete copy
                for (int i = 0; i < height; i++)    {
                    delete[] *(copy + i);
                }
                delete[] copy;
                
        return;
    }

    // Blur Filter Function
    void Image :: applyFilter() {
        // create a copy so org is not changed
        int** copy = new int* [height];
        for (int i = 0; i < height; i++)    {
            *(copy + i) = new int [width];
            for (int j = 0; j < width; j++) {
                *(*(copy + i) + j) = *(*(arrayOfPixels + i) + j);
            }
        }

        // note that there cannot be nine neighbours for any cell
        // on the boundary row or boundary col, so ignore them
        for (int i = 1; i < height - 1; i++)    {
            for (int j = 1; j < width - 1; j++) {
                // arry for all neighbours
                int size = 9;
                int arr[9], k = 0; // k is used to traverse arr
                
                // now in order to collect the neighbours we use
                // -1 0 and 1 as the neighbours are one prev, one
                // at same pos and one next

                for (int ni = -1; ni <= 1; ni++)    {
                    for (int nj = -1; nj <= 1; nj++)    {
                        *(arr + (k++)) = *(*(copy + (i + ni)) + (j + nj));
                    }
                }

                // calculate average
                int sum = 0;
                for (int x = 0; x < size; x++)  {
                    sum += *(arr + x);
                }
                int average = sum / 9;

                // now finally replace i,j with average
                *(*(arrayOfPixels + i) + j) = average; // here we change the value of 
                // org array and hence for future the neighbours would change, so we made a copy
            }
        } 
        // delete copy
                for (int i = 0; i < height; i++)    {
                    delete[] *(copy + i);
                }
                delete[] copy;
                
        return;
    }

int main() {
    // test readImage and saveImage
    Image img;
    img.readImage("sample.pgm");
    img.saveImage("output.pgm");
    cout << "readImage and saveImage: done" << endl;

    // test changeBrightness
    img.readImage("sample.pgm");
    img.changeBrightness(50);
    img.saveImage("output.pgm");
    cout << "changeBrightness +50: done" << endl;

    // test flipImage horizontal
    img.readImage("sample.pgm");
    img.flipImage("horizontal");
    img.saveImage("output.pgm");
    cout << "flipImage horizontal: done" << endl;

    // test flipImage vertical
    img.readImage("sample.pgm");
    img.flipImage("vertical");
    img.saveImage("output.pgm");
    cout << "flipImage vertical: done" << endl;

    // test negate
    img.readImage("sample.pgm");
    img.negate();
    img.saveImage("output.pgm");
    cout << "negate: done" << endl;

    // test combineImages
    Image img2;
    img.readImage("sample.pgm");
    img2.readImage("sample2.pgm");
    img.combineImages(img2);
    img.saveImage("output.pgm");
    cout << "combineImages: done" << endl;

    // test medianFilter
    img.readImage("sample.pgm");
    img.medianFilter();
    img.saveImage("output.pgm");
    cout << "medianFilter: done" << endl;

    // test applyFilter (blur)
    img.readImage("sample.pgm");
    img.applyFilter();
    img.saveImage("output.pgm");
    cout << "applyFilter blur: done" << endl;

    return 0;
}