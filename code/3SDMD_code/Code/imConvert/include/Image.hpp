#ifndef IMAGE_GUARD
#define IMAGE_GUARD

#include "CUDASkel2D/include/field.h"
#include "ImageWriter.hpp"
#include <set>
#include <vector>

class Image {
  private:
    /** VARIABLES **/
    float      islandThreshold;
    float             layerThreshold;
    int               DistinguishableInterval;
    double            *importance;
    //double            *UpperLevelSet;
    int               nPix; /* Short for (dimX * dimY) */
    string            compress_method;
    skel_tree_t *traceLayer(FIELD<float> *skel, FIELD<float> *dt);
    FIELD<float>   *sm_;
    //skel_tree_t *tracePath(int x, int y, FIELD<float> *skel, FIELD<float> *dt);
    //void tracePath(int x, int y, FIELD<float> *skel, FIELD<float> *dt, vector<Vector3<float>> Branch);
    //coord2D_list_t *neighbours(int x, int y, FIELD<float> *skel);//wang

  public:
    /** VARIABLES **/
    FIELD<float>   *im;
    int clear_color;
  int enterORnot = 0;
    /** CONSTRUCTORS **/
    Image(FIELD<float> *in);
    Image(FIELD<float> *in, float islandThresh, float importanceThresh, int GrayInterval, FIELD<float> *sm);

    /** DESTRUCTOR **/
    ~Image();

    /** FUNCTIONS **/
    //static void removeIslands(FIELD<float>*layer, unsigned int iThresh);
    void removeIslands();
    void removeLayers();
    void calculateImportance();
    void find_layers(int clear_color, double* importance_upper, double width);
    //std::vector<std::pair<int, skel_tree_t*>>* computeSkeletons(int *firstLayer);
    void computeSkeletons(float skel_saliency_thres);
    int CalculateCPnum(int i, FIELD<float> *imDupeCurr, int WriteToFile, float skel_saliency_thres);
    void computeCUDASkeletons();
    void removeDuplicatePoints(FIELD<float> *imPrev, FIELD<float> *skP, FIELD<float> *imCur, FIELD<float> *skC);
    pair<int, int> find_closest_point(int i, int j, FIELD<float>* skelPrev);
    void bundle(FIELD<float>* skelCurr, FIELD<float>* skelPrev, FIELD<float>* currDT, FIELD<float>* prevDT, short* prev_skel_ft, int fboSize);
    double overlap_prune(FIELD<float>* skelPrev, FIELD<float>* currDT, FIELD<float>* prevDT);
};

#endif
