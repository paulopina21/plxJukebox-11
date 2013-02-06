

#ifndef CONVOLUTIONKERNELS
#define CONVOLUTIONKERNELS

#include "system.h"
#include "../../../settings/VideoSettings.h"

class CConvolutionKernel
{
  public:
    CConvolutionKernel(ESCALINGMETHOD method, int size);
    ~CConvolutionKernel();

    int      GetSize()           { return m_size; }
    float*   GetFloatPixels()    { return m_floatpixels; }
    uint8_t* GetIntFractPixels() { return m_intfractpixels; }
    uint8_t* GetUint8Pixels()    { return m_uint8pixels; }

  private:

    void Lanczos2();
    void Lanczos3Fast();
    void Lanczos3();
    void Spline36Fast();
    void Spline36();
    void Bicubic(double B, double C);

    double LanczosWeight(double x, double radius);
    double Spline36Weight(double x);
    double BicubicWeight(double x, double B, double C);

    void ToIntFract();
    void ToUint8();

    int      m_size;
    float*   m_floatpixels;
    uint8_t* m_intfractpixels;
    uint8_t* m_uint8pixels;
};

#endif //CONVOLUTIONKERNELS
