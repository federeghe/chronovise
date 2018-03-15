#include "gtest/gtest.h"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include "statistical/estimator_pwm.hpp"
#include "utility/oop.hpp"

using namespace chronovise;

class EstimatorPWM_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    EstimatorPWM_Test() 
    {
        // You can do set-up work for each test here.
    }

    virtual ~EstimatorPWM_Test() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }


};

TEST_F(EstimatorPWM_Test, GPD_0_1_0) {

    constexpr int n_elem = 200;
    double xs[n_elem] =
    {
1.819034,0.230314,1.167271,0.637650,1.797886,0.507528,1.335710,0.424527,0.372203,0.290150,0.797305,2.479067,1.474134,0.090650,1.881391,0.191382,0.619260,0.003873,2.548799,0.814912,2.238177,0.038847,5.374286,0.255008,0.201745,0.140764,2.471763,0.916834,1.347572,0.223058,0.840687,0.093599,1.704589,1.332553,1.927311,1.994596,0.140076,0.545237,0.598091,1.931333,0.158959,0.474727,1.047105,0.666993,0.911781,2.577460,1.427466,2.092981,1.693321,1.427314,0.874029,3.002668,0.102347,0.056796,0.711588,0.714876,1.085540,0.105301,0.996290,2.196400,0.248138,0.942278,1.420094,0.906558,2.338684,2.025156,0.059696,0.044857,0.553023,2.817092,1.449107,1.040838,0.196996,4.173165,3.146002,1.777916,0.432145,0.312354,0.434257,0.796457,0.603290,1.216313,0.294783,1.666246,0.375748,1.695480,0.998356,0.469014,0.248170,2.511755,0.073231,0.253973,0.719919,0.830437,0.805681,1.183029,0.676273,0.671833,0.201348,0.229625,0.439563,0.971250,0.208772,0.629561,1.047747,0.062938,0.132454,0.597553,0.474052,0.532654,1.571457,1.199827,0.753060,1.467556,0.169237,1.635965,1.487566,1.767801,1.479883,0.830804,1.167634,0.079715,0.843488,1.688393,0.099952,0.020459,0.823552,2.197152,1.354545,0.894725,0.519369,1.338603,0.506098,0.340779,1.506219,2.142018,1.215115,1.143259,0.857629,0.677553,2.459054,1.337572,0.221876,3.532892,0.073804,0.314258,0.716193,0.547273,1.438499,0.779034,0.037610,0.603662,0.651745,1.462768,0.715602,0.471509,0.386935,0.927566,1.001204,0.012091,3.277065,0.121978,0.090705,0.227925,2.315546,1.339903,1.092560,0.386063,1.991041,0.326801,2.237155,0.425019,0.704868,0.249678,0.335421,0.101235,0.115498,1.096126,0.358468,1.620449,3.488687,0.295614,0.693102,0.734131,0.100127,0.494515,0.481807,0.151472,0.216305,0.550396,1.698693,1.427400,0.120461,3.551759,0.713551,1.784225,0.021550,0.338702,0.692204, 0.693211};

    MeasuresPool<int, double> mp;
    for (int i=0; i<n_elem; i++) {
        mp.push(0, xs[i]);
    }

    Estimator_PWM<int, double> mle;
    mle.set_source_evt_approach(&typeid(EVTApproach_PoT<int, double>));
    mle.run(mp);
    auto res = mle.get_result();

    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_location(), 0., 5e-1);    
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_scale(), 1, 5e-1);
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_shape(), 0., 5e-1);

}



TEST_F(EstimatorPWM_Test, GPD_2_20_1) {

    constexpr int n_elem = 200;
    double xs[n_elem] =
    {
2.972253,12.615112,7.854437,12.186839,14.686876,9.724292,8.931033,17.720373,10.825809,2.873886,4.324948,2.573393,9.363876,13.881676,13.124022,21.863925,15.303356,6.609077,9.077864,13.039553,3.194545,2.428168,12.156383,13.166223,6.046873,19.590124,5.452777,7.074252,10.263555,15.940262,10.298249,10.502486,17.870576,20.857918,17.409326,2.219657,5.872224,21.140228,11.152038,16.706098,11.817679,10.357776,21.088323,4.483723,12.320992,18.115788,2.373304,3.947349,9.443776,14.620806,3.432844,4.029801,20.958898,20.237815,17.227604,15.312286,4.914226,21.698486,16.830726,7.574872,20.229929,4.759897,18.666830,12.968636,16.324473,11.045289,2.571211,19.024144,4.633637,12.231589,10.181876,21.932225,12.288877,7.371050,11.260571,2.269745,11.968961,21.005518,19.790748,12.570655,18.697562,12.889600,9.662577,19.700337,20.348584,21.619802,20.255484,13.717492,13.159500,4.875694,17.189338,5.132981,14.503189,21.619719,7.077687,18.711226,21.600973,10.293159,6.018056,8.367920,16.037691,11.298308,18.505867,11.354837,17.756975,8.312181,14.236784,17.408095,10.497336,19.384572,16.302854,20.472004,14.213144,4.590434,9.765381,14.664925,9.097005,9.658657,15.246266,18.689049,3.100474,11.800784,2.925731,12.601912,3.341977,6.165653,12.114481,21.726561,17.195699,13.242380,4.240435,3.735613,9.526876,12.615748,5.516989,14.747101,8.664883,15.034160,19.524621,12.671436,21.198630,11.065567,2.743819,18.308146,21.159540,13.087160,14.085170,2.596475,8.612978,7.396533,19.806913,12.100668,3.491440,8.557256,13.532752,15.623421,2.164351,6.911866,15.488838,14.436164,10.631625,7.352881,13.800982,9.726953,2.559820,4.876822,14.302165,16.537489,5.310755,12.155094,12.585103,19.095248,19.994198,15.940793,2.330914,20.446230,16.749579,14.743267,9.133148,20.073035,21.506312,15.766427,2.915881,3.894031,7.432066,8.885687,9.675695,17.727717,7.845240,18.250215,4.123982,20.837789,15.539371,4.930078,19.568696,6.999093,12.546647,15.949105,9.953557,17.752163
};
    
    MeasuresPool<int, double> mp;
    for (int i=0; i<n_elem; i++) {
        mp.push(0, xs[i]);
    }

    Estimator_PWM<int, double> mle;
    mle.set_source_evt_approach(&typeid(EVTApproach_PoT<int, double>));
    mle.run(mp);
    auto res = mle.get_result();

    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_location(), 2., 5e-1);    
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_scale(), 20., 5e-1);
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_shape(), -1., 5e-1);

}


TEST_F(EstimatorPWM_Test, GEV_05_1_2) {

    constexpr int n_elem = 1000;
    double xs[n_elem] =
    {

3.685120,5.923758,1.680537,1.399140,1.637720,1.952002,1.790303,7.289595,1.160557,2.765210,1.484692,4.763889,1.496372,2.409891,77.223768,1.966376,1.144080,1.609887,2.083212,1.909002,1.648784,7.784316,3.240236,10.176761,2.201130,8.063643,0.881819,2.846148,4.246679,1.657031,7.563628,3.847912,4.580890,2.682062,4.148166,1.896973,1.633803,1.854147,2.729353,4.632000,1.798753,2.096656,5.191155,2.867235,21.258236,1.585549,4.591968,3.195333,1.696070,2.320586,2.086726,2.795734,4.240084,1.332404,4.509566,4.807623,1.963968,2.177249,2.676922,3.354376,3.665112,3.798516,2.058636,2.174949,9.466358,2.679994,4.956116,1.763567,2.904061,2.746140,10.367354,1.276571,2.403975,2.479028,1.289356,6.318589,5.705946,2.204227,4.030298,1.448133,2.891778,1.724729,2.224685,4.856381,1.567196,1.832461,2.345440,1.919826,4.216014,17.823525,1.475000,1.666549,3.363912,2.020746,12.251968,11.934150,3.013314,5.151835,2.094737,2.952129,16.399270,2.624428,7.629595,3.492005,2.347924,2.988731,5.793025,1.573402,2.076201,22.565444,2.096076,3.096222,6.205804,29.396129,3.064516,1.341831,1.097465,2.883392,2.655732,10.156398,3.695549,3.116980,2.485335,1.722935,10.160363,2.548632,1.069413,3.324324,2.472204,1.188940,5.859761,1.899986,1.649025,1.357061,1.850416,1.645929,3.058107,1.213643,1.761300,1.777173,5.595460,2.220596,3.780809,2.813425,4.046536,1.357012,13.586528,4.936071,1.158008,2.289438,1.888203,2.943374,1.650484,2.709327,2.812779,2.797744,2.233268,1.094289,2.450914,2.111531,1.340743,2.269215,2.240908,2.591148,4.299228,3.354547,5.409441,1.163888,1.624579,2.268473,9.718514,4.119861,2.244005,1.908376,1.189170,3.652199,2.425981,1.576313,2.168644,1.499194,3.743552,2.001282,8.168817,0.992041,4.619200,2.925211,2.543060,3.049963,3.539194,1.302089,5.534371,0.970924,1.808384,1.527086,7.228025,1.220421,2.714516,2.978948,3.054122,5.243895,1.177847,4.446713,2.506050,3.311429,1.606822,2.560464,3.365835,9.476341,2.221248,1.275041,1.182882,2.939562,4.189172,3.290922,1.939538,8.555309,2.473928,9.197214,1.238166,1.593698,3.961706,6.677090,4.038990,1.811479,1.456756,4.923956,4.063423,1.749909,1.644412,1.876267,4.626734,4.519924,2.670416,2.675207,1.787640,3.343035,4.190082,2.212173,2.226414,2.287703,1.770256,3.192402,6.283933,6.457263,3.704806,1.724453,3.280944,1.405028,1.382930,1.554179,1.441131,2.731616,1.237411,4.521947,3.511041,7.205892,2.376948,3.074018,5.862228,2.542217,1.778132,12.820455,1.098887,1.889731,12.091891,1.992276,1.845903,1.375980,6.742201,1.414587,1.904965,6.081175,2.401028,2.869867,2.723320,3.337171,1.064634,2.502188,1.078368,4.590991,1.925526,4.902964,1.689018,2.716230,7.884173,1.146891,1.170575,1.015138,3.229629,2.792049,1.357284,4.189937,2.882226,1.227152,1.224069,1.415968,4.107142,1.295960,1.668965,1.683092,1.331710,5.117448,3.336811,3.594440,3.050089,2.459736,1.890103,3.112759,1.366929,1.446476,1.009656,10.488410,11.532628,1.383893,2.293330,3.084096,1.798059,3.768548,2.618948,2.170432,1.740922,3.761466,6.109435,3.553096,2.108936,7.926238,1.711957,2.521910,9.294723,1.742288,1.698851,7.299256,1.221758,1.821215,2.760387,1.584571,2.972387,4.214658,2.408152,3.051625,4.186587,1.657988,2.802131,1.352978,2.457917,4.754803,6.962129,2.396116,1.766709,3.060977,6.807211,2.436743,12.368463,1.569829,1.349455,1.816059,2.079181,2.149540,1.851824,3.308116,1.294407,2.095323,1.810591,1.839165,1.333788,2.770396,1.779433,1.465329,0.738954,1.781596,2.589849,5.379424,1.124364,6.320525,1.402773,4.690045,4.239437,6.832328,1.419347,2.418737,2.103550,1.511356,2.689314,2.826970,1.611804,2.472990,19.180218,2.367696,3.314850,2.122219,1.091283,1.804691,4.251059,1.942694,1.268694,2.441245,1.997159,3.640526,2.490577,4.288368,4.447466,1.550659,1.383446,4.503357,2.982825,0.984409,6.033917,2.456512,2.565269,2.828015,3.821759,5.059673,2.041174,1.272765,3.595478,1.904630,4.785681,2.010476,4.606752,1.518673,1.398936,5.590920,1.131956,3.262384,3.594683,2.198695,2.032781,13.950815,2.086494,2.207882,1.469344,1.889188,1.858424,5.989806,1.691354,1.849795,2.114821,3.403567,1.435745,5.388827,1.268203,2.275141,1.070012,3.756746,3.349121,1.611966,3.219937,2.615631,4.973331,2.620749,6.219953,2.145891,1.973666,2.364558,1.713270,7.378901,2.291224,1.708472,2.180699,3.365901,2.096014,1.531846,5.076868,2.727953,2.015553,1.629491,1.622903,2.481377,2.187339,3.655480,1.227928,4.913827,3.219787,1.417648,5.118413,1.576090,2.832206,2.559556,1.483250,0.879127,3.926570,3.862205,2.150466,1.180977,2.734683,1.512806,3.554379,2.526158,1.706157,6.796829,3.801325,5.776496,1.222475,1.536015,3.621021,3.326967,3.981536,2.408856,2.163588,2.850547,5.067736,3.165094,2.486358,1.819740,3.375698,2.037685,2.657966,5.799169,4.838653,6.122873,7.972209,4.427712,0.778389,0.831937,1.281295,1.724984,1.028546,2.159392,1.928359,2.553044,7.221654,1.818943,1.920541,5.139578,1.926818,1.421471,2.429523,5.084628,2.045190,3.320218,2.931783,2.239366,2.313485,8.804301,1.269250,1.772219,2.228863,2.742667,5.535825,2.298793,2.199443,3.696221,2.294945,5.166367,2.290436,2.395690,2.359306,1.648458,1.275509,1.217757,5.813772,1.657485,5.181815,3.429722,5.422585,7.905497,1.425544,2.072057,14.275319,3.019150,6.047912,2.341893,0.968768,2.906802,1.652427,2.500524,3.526757,2.832561,2.746161,2.187375,1.684376,2.173925,0.933766,2.839150,9.652334,1.304881,1.095061,5.754997,1.691152,0.920573,4.420875,1.427642,5.590494,1.304678,1.958776,2.768575,2.732218,3.146803,3.036504,2.187177,1.425724,3.745603,1.678541,3.049700,5.098443,1.271916,11.887139,1.075356,4.716152,4.721006,1.154973,2.570565,8.268353,1.877424,4.312383,2.804696,4.115166,4.224237,1.153840,1.780607,3.066133,2.366817,12.055398,3.715845,2.658612,1.820115,1.713632,5.763852,2.228224,4.435074,1.313248,5.141818,1.055723,6.134327,6.159471,2.488245,1.374059,1.521835,3.390378,4.653773,1.091550,3.798106,9.552589,1.933110,2.984626,1.933466,1.616747,4.077870,3.512441,1.769758,2.720286,2.150278,1.294988,1.035760,2.371870,1.768338,1.924925,1.790965,1.504713,2.087262,3.333156,1.585494,3.138919,2.216706,2.186954,1.515499,1.559828,2.875319,1.745408,2.625238,8.391891,3.449240,3.215739,9.821469,3.964783,2.834017,8.654985,1.191109,1.744671,17.271272,3.933664,2.319170,3.226056,2.138303,2.033639,1.608935,2.041367,1.066353,2.309253,1.908232,12.790140,2.608229,4.895890,2.112494,2.276035,4.578815,21.276932,2.487663,7.184706,3.636798,2.656912,11.229552,4.552764,9.849817,3.027454,2.032047,2.323178,6.585360,0.974799,1.469056,2.306800,2.559351,1.191284,3.091577,5.848461,1.345157,2.200522,1.773217,16.404685,2.838856,1.707837,1.407088,2.567141,4.600693,4.741471,4.684172,1.585589,2.564865,5.471821,1.376216,5.078773,6.154300,1.620148,1.248971,2.315438,4.710244,2.299741,2.129051,2.411793,1.388110,1.406223,5.369910,2.811828,1.736253,5.247663,1.185649,2.262490,3.505861,1.922937,2.092841,2.498842,5.981864,3.995485,1.224362,1.769623,2.031484,5.244948,2.147195,1.673873,2.787629,2.332513,6.114873,7.696876,4.460650,3.409832,3.671348,6.152156,1.210525,1.914855,0.857413,4.604987,2.428240,1.995338,1.641555,2.528198,1.796305,1.221055,1.273744,1.220950,2.117563,1.382611,2.216554,6.127384,1.961653,1.374001,2.663875,5.473929,1.948184,1.122963,1.432399,1.247747,3.649090,2.258609,3.150118,3.343787,2.673231,2.935748,5.538964,3.116042,5.482873,2.293675,1.429807,1.220267,3.447595,1.842946,3.167263,3.060432,2.513981,3.453809,2.419011,2.361222,2.394772,7.775222,2.059065,1.365787,1.675208,3.250980,4.777608,11.487783,1.613570,3.820907,2.727525,2.097793,2.437456,2.387225,3.054664,3.675395,1.827660,1.287708,4.573866,2.059921,3.964487,1.525736,1.344403,6.335799,5.505057,138.856391,5.236252,1.100938,2.565891,40.938732,2.440895,5.438615,1.227178,17.860307,7.051853,2.643878,2.181431,1.919912,3.494817,0.965203,2.016873,7.050513,2.572875,2.314364,2.390292,1.845449,8.907644,14.836888,2.450012,23.190415,2.256461,2.165207,1.608799,1.559944,4.675032,3.539252,2.509116,4.619569,2.443980,2.594393,1.608970,2.743762,1.433492,1.164007,3.240977,2.837920,1.624517,2.107351,2.941871,2.607686,1.393798,1.500462,0.760927,2.141906,2.362863,1.477070,3.141893,0.997284,1.372644,9.029679,12.792598,1.072648,2.381190,5.204688,1.681204,4.698436,4.403351,2.937156,0.809638,2.032463,6.309517,3.222683,2.029975,2.952250,1.682167,2.673465,14.728113,4.955399,1.781219,3.235692,1.973655,17.434574,1.270744,1.699393,4.374159,1.272077,2.514748,4.241277,3.635183,1.430652,2.200890,1.952976,2.329515,2.741930,1.441320,6.341858,2.994819,1.484795,2.650648,7.514634,4.044802,3.255871,2.289494,1.723977,2.664527,1.695632,1.871843,6.543167,5.727884,4.170925,7.203457,1.524426,2.464321,2.927281,6.636513,3.125302,2.058816,3.644839,4.457236,2.799871,1.273824,7.035025,1.169162,2.499010,1.370421,2.033621,4.393428,1.684188,5.706832,3.436196,2.028113,1.695996,1.705640,3.885503,1.154990,3.253365,2.894034,3.700454,13.185605,2.044077,1.723700,5.531852,4.307780,2.273176,1.291717,2.643911,1.545519,2.516379,1.965377,1.860268,3.540048,2.457943,4.126507,1.587490,3.208940,1.164995,4.247834,3.211760,8.489278,1.293481,6.454023,2.437146,2.868022,1.863562,1.250577,4.972160,1.438034,2.007097,2.904394,40.397042,2.463609,20.482849,1.641298,2.083684,3.326002,1.208485,3.708764,2.148492,4.373783};
    MeasuresPool<int, double> mp;
    for (int i=0; i<n_elem; i++) {
        mp.push(0, xs[i]);
    }

    Estimator_PWM<int, double> mle;
    mle.set_source_evt_approach(&typeid(EVTApproach_BM<int, double>));
    mle.run(mp);
    auto res = mle.get_result();

    ASSERT_TRUE(instanceof_ptr<GEV_Distribution>(res));

    EXPECT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 2, 5e-1);    
    EXPECT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 1., 5e-1);
    EXPECT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), -0.5, 5e-1);

}





