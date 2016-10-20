
/**
*
*	index_generator.cpp
*
**/

#include"index_generator.hpp"
#include"_include_opengl.hpp"
#include<cassert>
namespace aab	{
namespace visen	{

StripQuadIndexGenerator stripQuadIndexGenerator;
QuadsIndexGenerator quadsIndexGenerator;

#define TEST_INDEX_VALUE_METHODS

////////////////////////////////////////////////////////////////////////////////
//  StripQuadIndexGenerator
////////////////////////////////////////////////////////////////////////////////

// 0 1 2 3 3 4  4 5 6 7 7 8  8 9 10 11 11 12  12 13 14 15 15 16  16 17 18 19 19 20  etc

// 0 1 2 3 acts as triangle strip to produce quad.
// 3 3 degenerates at vertex 3, and 4 4 degenerates at vertex four.
// then 4 5 6 7 acts as another triangle strip to produce the next quad.
// Strip quad has the form:
    //VertexT v00;
    //VertexT v01;
    //VertexT v10;
    //VertexT v11;
    
void StripQuadIndexGenerator::generateIndices(std::vector<VertexIndex>&vector, const unsigned int quads,unsigned int&renderType)
{
    vector.reserve(6*quads);
    
    VertexIndex newQuad[6];
    
    for (unsigned int t = 0; t< 4*quads; t += 4)
    {
        newQuad[0] = t;
        newQuad[1] = t+1;
        newQuad[2] = t+2;
        newQuad[3] = t+3;
        newQuad[4] = t+3;
        newQuad[5] = t+4;
        vector.insert(vector.end(),newQuad,newQuad+6); 
    }
    
    // todio - remove last few redundant indices?
    
    renderType = GL_TRIANGLE_STRIP;
    
    #ifdef TEST_INDEX_VALUE_METHODS    
    for (unsigned int index = 0; index < vector.size();++index)
    {
        assert (getIndexValue(index) == vector[index]);
    }
    
    for (unsigned int value = 0; value < 4*vector.size()/6; ++value)
    {
        assert(vector[getValuesFirstIndex(value)] == value && "02");
    }
    #endif
}

unsigned int StripQuadIndexGenerator::getIndexValue(unsigned int index)
{
    static unsigned int per_quad_value[6] = { 0, 1, 2, 3, 3, 4 };
    
    return 4*static_cast<unsigned int>(index/6) + per_quad_value[index%6];
}

//value: 0 1 2 3 3 4  4 5 6 7 7  8   8  9  10 11 11 12  12 13 14 15 15 16  16 17 18 19 19 20  
//index: 0 1 2 3 4 5  6 7 8 9 10 11  12 13 14 15 16 17  18 19 20 21 22 23  24 25 26 27 28 29

//quad:                 0          1        2            3            4
//4*quad:               0          4        8            12           16
//VALUE:                0 1 2 3 4  5 6 7 8  9  10 11 12  13 14 15 16  17 18 19 20
//value_within_quad:    0 0 1 2 3  0 1 2 3  0  1   2  3  0  1  2  3   0  1  2  3
//val_to_per_quad_index:0 1 2 3 5  1 2 3 5  1  2   3  5  1  2  3  5   1  2  3  5
//6*quad:               0 0        6        12           18           24
//first index:          0 1 2 3 5  7 8 9 11 13 14 15 17  19 20 21 23  25 26 27 29 
      

unsigned int StripQuadIndexGenerator::getValuesFirstIndex(unsigned int value)
{
    if (!value)
    {
        return 0;
    }
    
    static unsigned int per_quad_value_to_index[4] = { 1, 2, 3, 5 };
    const unsigned int quad = (value-1)/4;
    const unsigned int value_within_quad = value - 4*quad - 1;
    
    return 6*quad + per_quad_value_to_index[value_within_quad];
}

unsigned int StripQuadIndexGenerator::getObjectIndexFromStartingValue(unsigned int value)
{
    return 6*static_cast<unsigned int>(value/4);
}

////////////////////////////////////////////////////////////////////////////////
//  StripQuadAsQuadIndexGenerator
////////////////////////////////////////////////////////////////////////////////

/*
void StripQuadAsQuadIndexGenerator::generateIndices(std::vector<VertexIndex>&vector, const unsigned int quads,unsigned int&renderType)
{
    vector.reserve(4*quads);
    
    VertexIndex newQuad[4];
    
    for (unsigned int t = 0; t< 4*quads; t += 4)
    {
        newQuad[0] = t+0;
        newQuad[1] = t+1;
        newQuad[2] = t+3;
        newQuad[3] = t+2;
        vector.insert(vector.end(),newQuad,newQuad+4);
    }
    
    renderType = GL_QUADS;
}

unsigned int QuadsIndexGenerator::getIndexValue(unsigned int index) // to be tested
{
    static unsigned int per_quad_value[6] = { 0, 1, 3, 2 };
    
    return 4*static_cast<unsigned int>(index/4) + per_quad_value[index%4];
}

unsigned int QuadsIndexGenerator::getValuesFirstIndex(unsigned int value) // to be tested
{
    static unsigned int per_quad_value_to_index[4] = { 0, 1, 3, 2 };
    const unsigned int quad_value = 4*static_cast<unsigned int>(value/4);
    const unsigned int value_within_quad = value - quad_value;        
    
    return quad_value + per_quad_value_to_index[value_within_quad];
}
*/

////////////////////////////////////////////////////////////////////////////////
//  QuadsIndexGenerator
////////////////////////////////////////////////////////////////////////////////

void QuadsIndexGenerator::generateIndices(std::vector<VertexIndex>&vector, const unsigned int quads,unsigned int&renderType)
{
    vector.reserve(4*quads);
    
    VertexIndex newQuad[4];
    
    //optimize:  simply push_back an increasing value until 4*quads
    for (unsigned int t = 0; t< 4*quads; t += 4)
    {
        newQuad[0] = t+0;
        newQuad[1] = t+1;
        newQuad[2] = t+2;
        newQuad[3] = t+3;
        vector.insert(vector.end(),newQuad,newQuad+4);
    }
    
    renderType = GL_QUADS;
    
    #ifdef TEST_INDEX_VALUE_METHODS    
    for (unsigned int index = 0; index < vector.size();++index)
    {
        assert (getIndexValue(index) == vector[index]);
    }
    
    for (unsigned int value = 0; value < vector.size();++value)
    {
        assert(vector[getValuesFirstIndex(value)] == value);
    }
    #endif
}

unsigned int QuadsIndexGenerator::getIndexValue(unsigned int index)
{
    return index;
}

unsigned int QuadsIndexGenerator::getValuesFirstIndex(unsigned int value)
{
    return value;
}

unsigned int QuadsIndexGenerator::getObjectIndexFromStartingValue(unsigned int value)
{
    return value;
}


VertexIndex staticIndexList[VISEN_MAX_STATIC_INDEX] = 
{
0,1,2,3,3,4,
4,5,6,7,7,8,
8,9,10,11,11,12,
12,13,14,15,15,16,
16,17,18,19,19,20,
20,21,22,23,23,24,
24,25,26,27,27,28,
28,29,30,31,31,32,
32,33,34,35,35,36,
36,37,38,39,39,40,
40,41,42,43,43,44,
44,45,46,47,47,48,
48,49,50,51,51,52,
52,53,54,55,55,56,
56,57,58,59,59,60,
60,61,62,63,63,64,
64,65,66,67,67,68,
68,69,70,71,71,72,
72,73,74,75,75,76,
76,77,78,79,79,80,
80,81,82,83,83,84,
84,85,86,87,87,88,
88,89,90,91,91,92,
92,93,94,95,95,96,
96,97,98,99,99,100,
100,101,102,103,103,104,
104,105,106,107,107,108,
108,109,110,111,111,112,
112,113,114,115,115,116,
116,117,118,119,119,120,
120,121,122,123,123,124,
124,125,126,127,127,128,
128,129,130,131,131,132,
132,133,134,135,135,136,
136,137,138,139,139,140,
140,141,142,143,143,144,
144,145,146,147,147,148,
148,149,150,151,151,152,
152,153,154,155,155,156,
156,157,158,159,159,160,
160,161,162,163,163,164,
164,165,166,167,167,168,
168,169,170,171,171,172,
172,173,174,175,175,176,
176,177,178,179,179,180,
180,181,182,183,183,184,
184,185,186,187,187,188,
188,189,190,191,191,192,
192,193,194,195,195,196,
196,197,198,199,199,200,
200,201,202,203,203,204,
204,205,206,207,207,208,
208,209,210,211,211,212,
212,213,214,215,215,216,
216,217,218,219,219,220,
220,221,222,223,223,224,
224,225,226,227,227,228,
228,229,230,231,231,232,
232,233,234,235,235,236,
236,237,238,239,239,240,
240,241,242,243,243,244,
244,245,246,247,247,248,
248,249,250,251,251,252,
252,253,254,255,255,256/*,
256,257,258,259,259,260,
260,261,262,263,263,264,
264,265,266,267,267,268,
268,269,270,271,271,272,
272,273,274,275,275,276,
276,277,278,279,279,280,
280,281,282,283,283,284,
284,285,286,287,287,288,
288,289,290,291,291,292,
292,293,294,295,295,296,
296,297,298,299,299,300,
300,301,302,303,303,304,
304,305,306,307,307,308,
308,309,310,311,311,312,
312,313,314,315,315,316,
316,317,318,319,319,320,
320,321,322,323,323,324,
324,325,326,327,327,328,
328,329,330,331,331,332,
332,333,334,335,335,336,
336,337,338,339,339,340,
340,341,342,343,343,344,
344,345,346,347,347,348,
348,349,350,351,351,352,
352,353,354,355,355,356,
356,357,358,359,359,360,
360,361,362,363,363,364,
364,365,366,367,367,368,
368,369,370,371,371,372,
372,373,374,375,375,376,
376,377,378,379,379,380,
380,381,382,383,383,384,
384,385,386,387,387,388,
388,389,390,391,391,392,
392,393,394,395,395,396,
396,397,398,399,399,400,
400,401,402,403,403,404,
404,405,406,407,407,408,
408,409,410,411,411,412,
412,413,414,415,415,416,
416,417,418,419,419,420,
420,421,422,423,423,424,
424,425,426,427,427,428,
428,429,430,431,431,432,
432,433,434,435,435,436,
436,437,438,439,439,440,
440,441,442,443,443,444,
444,445,446,447,447,448,
448,449,450,451,451,452,
452,453,454,455,455,456,
456,457,458,459,459,460,
460,461,462,463,463,464,
464,465,466,467,467,468,
468,469,470,471,471,472,
472,473,474,475,475,476,
476,477,478,479,479,480,
480,481,482,483,483,484,
484,485,486,487,487,488,
488,489,490,491,491,492,
492,493,494,495,495,496,
496,497,498,499,499,500,
500,501,502,503,503,504,
504,505,506,507,507,508,
508,509,510,511,511,512,
512,513,514,515,515,516,
516,517,518,519,519,520,
520,521,522,523,523,524,
524,525,526,527,527,528,
528,529,530,531,531,532,
532,533,534,535,535,536,
536,537,538,539,539,540,
540,541,542,543,543,544,
544,545,546,547,547,548,
548,549,550,551,551,552,
552,553,554,555,555,556,
556,557,558,559,559,560,
560,561,562,563,563,564,
564,565,566,567,567,568,
568,569,570,571,571,572,
572,573,574,575,575,576,
576,577,578,579,579,580,
580,581,582,583,583,584,
584,585,586,587,587,588,
588,589,590,591,591,592,
592,593,594,595,595,596,
596,597,598,599,599,600,
600,601,602,603,603,604,
604,605,606,607,607,608,
608,609,610,611,611,612,
612,613,614,615,615,616,
616,617,618,619,619,620,
620,621,622,623,623,624,
624,625,626,627,627,628,
628,629,630,631,631,632,
632,633,634,635,635,636,
636,637,638,639,639,640,
640,641,642,643,643,644,
644,645,646,647,647,648,
648,649,650,651,651,652,
652,653,654,655,655,656,
656,657,658,659,659,660,
660,661,662,663,663,664,
664,665,666,667,667,668,
668,669,670,671,671,672,
672,673,674,675,675,676,
676,677,678,679,679,680,
680,681,682,683,683,684,
684,685,686,687,687,688,
688,689,690,691,691,692,
692,693,694,695,695,696,
696,697,698,699,699,700,
700,701,702,703,703,704,
704,705,706,707,707,708,
708,709,710,711,711,712,
712,713,714,715,715,716,
716,717,718,719,719,720,
720,721,722,723,723,724,
724,725,726,727,727,728,
728,729,730,731,731,732,
732,733,734,735,735,736,
736,737,738,739,739,740,
740,741,742,743,743,744,
744,745,746,747,747,748,
748,749,750,751,751,752,
752,753,754,755,755,756,
756,757,758,759,759,760,
760,761,762,763,763,764,
764,765,766,767,767,768,
768,769,770,771,771,772,
772,773,774,775,775,776,
776,777,778,779,779,780,
780,781,782,783,783,784,
784,785,786,787,787,788,
788,789,790,791,791,792,
792,793,794,795,795,796,
796,797,798,799,799,800,
800,801,802,803,803,804,
804,805,806,807,807,808,
808,809,810,811,811,812,
812,813,814,815,815,816,
816,817,818,819,819,820,
820,821,822,823,823,824,
824,825,826,827,827,828,
828,829,830,831,831,832,
832,833,834,835,835,836,
836,837,838,839,839,840,
840,841,842,843,843,844,
844,845,846,847,847,848,
848,849,850,851,851,852,
852,853,854,855,855,856,
856,857,858,859,859,860,
860,861,862,863,863,864,
864,865,866,867,867,868,
868,869,870,871,871,872,
872,873,874,875,875,876,
876,877,878,879,879,880,
880,881,882,883,883,884,
884,885,886,887,887,888,
888,889,890,891,891,892,
892,893,894,895,895,896,
896,897,898,899,899,900,
900,901,902,903,903,904,
904,905,906,907,907,908,
908,909,910,911,911,912,
912,913,914,915,915,916,
916,917,918,919,919,920,
920,921,922,923,923,924,
924,925,926,927,927,928,
928,929,930,931,931,932,
932,933,934,935,935,936,
936,937,938,939,939,940,
940,941,942,943,943,944,
944,945,946,947,947,948,
948,949,950,951,951,952,
952,953,954,955,955,956,
956,957,958,959,959,960,
960,961,962,963,963,964,
964,965,966,967,967,968,
968,969,970,971,971,972,
972,973,974,975,975,976,
976,977,978,979,979,980,
980,981,982,983,983,984,
984,985,986,987,987,988,
988,989,990,991,991,992,
992,993,994,995,995,996,
996,997,998,999,999,1000,
1000,1001,1002,1003,1003,1004,
1004,1005,1006,1007,1007,1008,
1008,1009,1010,1011,1011,1012,
1012,1013,1014,1015,1015,1016,
1016,1017,1018,1019,1019,1020,
1020,1021,1022,1023,1023,1024*/
};
    
    
/*
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,
57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,
84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,
108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147
,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,
168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,
188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,
228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,
248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,
268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,
288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,
308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,
328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,
348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,
368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,
388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,
408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,
428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,
448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,
468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,
488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,
508,509,510,511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,
528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,
548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,
568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,
588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,
608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,
628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,
648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,
668,669,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,
688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,
708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,
728,729,730,731,732,733,734,735,736,737,738,739,740,741,742,743,744,745,746,747,
748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,
768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,
788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,
808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,
828,829,830,831,832,833,834,835,836,837,838,839,840,841,842,843,844,845,846,847,
848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,865,866,867,
868,869,870,871,872,873,874,875,876,877,878,879,880,881,882,883,884,885,886,887,
888,889,890,891,892,893,894,895,896,897,898,899,900,901,902,903,904,905,906,907,
908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,
928,929,930,931,932,933,934,935,936,937,938,939,940,941,942,943,944,945,946,947,
948,949,950,951,952,953,954,955,956,957,958,959,960,961,962,963,964,965,966,967,
968,969,970,971,972,973,974,975,976,977,978,979,980,981,982,983,984,985,986,987,
988,989,990,991,992,993,994,995,996,997,998,999,1000,1001,1002,1003,1004,1005,
1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,
1022,1023*/



}		//	visen
}		//	aab





