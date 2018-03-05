#include "gtest/gtest.h"
#include "evt/gev_distribution.hpp"
#include "statistical/estimator_mle.hpp"
#include "utility/oop.hpp"

#define MAX_VALUE 100000
#define MAX_VALUE_F 2.0

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class EstimatorMLE_Test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	EstimatorMLE_Test() 
	{
		// You can do set-up work for each test here.
	}

	virtual ~EstimatorMLE_Test() {
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

TEST_F(EstimatorMLE_Test, EVT_1_1_05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{0.191028, 2.23268, 0.125111, 0.23119, 1.47925, 0.308607, 3.4642, 3.45605, 2.50758, 0.45171, 2.10044, 1.46814, 11.083, 2.04172, 3.2378, 1.25003, 1.18423, 3.56445, 0.269165, 0.408548, 0.5109, 1.06371, 3.65408, 3.27426, 0.194038, 1.08725, 1.49846, 1.13791, 2.08502, 1.93213, 0.802566, 1.182, -0.020331, 14.7796, 0.495391, 0.335627, 1.01235, 0.571887, 1.36693, 0.924233, 7.98221, 5.94123, 0.165715, 2.62736, 0.745677, 1.15569, 1.57831, 7.23611, 1.14068, 14.2976, 0.8264, 2.35622, 2.13899, 1.54451, 2.33618, 2.14009, 0.522673, 0.394952, 64.937, 0.505256, 0.0809362, 1.6314, 4.64075, 2.15554, 0.553025, 1.00282, 1.27192, 13.6913, 0.468325, 4.06301, 2.01899, 1.02295, 0.55423, 1.17181, 1.3412, 0.37517, 1.75119, 0.640452, 1.04604, 1.72269, 0.703071, 0.798698, 1.87855, 0.736201, 3.551, 14.1235, 2.56705, 0.935762, 1.72738, 0.339971, 5.37655, 4.58522, 3.45894, 0.724986, 1.77276, 0.0268325, 1.16288, 0.854995, 0.481138, 0.524243, 1.15584, 0.301331, 1.79157, 1.30471, 2.32192, 2.34808, 1.98612, 0.0857522, 0.222501, 0.872608, 1.51329, 2.0716, 1.11121, 3.4893, 2.47741, 10.2062, 1.51505, 0.886892, 0.33398, 1.84923, 3.00001, 1.15752, 0.291307, 0.739138, 0.46136, 0.775145, 1.20757, 1.49945, 1.26145, 4.48188, 1.46617, 7.30248, 1.98184, 8.6195, 0.675901, 2.19691, 0.795253, 2.17108, 2.3166, 0.219795, 0.710392, 0.635213, 2.14768, 3.86305, 0.937306, 3.01775, 2.19214, -0.105874, 1.80824, 1.05204, 5.75165, -0.231171, 1.27741, 1.16018, 1.27252, 2.91362, 0.879995, 3.06219, 1.30611, 0.0958536, 0.517075, 2.5025, 1.31305, 0.458983, 0.928516, 1.83244, 0.556249, 2.63196, 0.68114, 5.81261, 0.745534, 2.86893, 0.548668, 0.791336, 0.292166, 1.69366, 2.24132, 1.57332, 1.16428, 2.01728, 2.03429, 2.2145, 1.97189, 7.42256, 0.598348, 2.41244, 0.664964, 0.371889, 1.83204, 1.23859, 1.26557, 2.11372, 2.91485, 0.952545, 2.11409, 1.13603, 3.8216, 3.67753, 0.714446, 1.86112};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_TRUE(instanceof_ptr<GEV_Distribution>(res));

	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 1., 1e-1);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 1., 1e-1);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), 0.5, 1e-1);	

}

TEST_F(EstimatorMLE_Test, EVT_0_1_M05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{1.7796, -0.66039, -0.32861, 0.077164, -1.2272, 0.76767, 0.091768, 1.7368, 0.091235, 0.61876, -0.73379, 0.036279, -0.70224, 0.94753, 1.2571, -0.047052, 0.77109, -0.21239, 0.40791, 1.1435, 0.56471, -0.090642, -0.19687, 0.21926, 0.14396, -0.022618, 0.47314, 0.90881, 0.14826, 0.16101, -0.88476, -1.8532, -0.22462, -0.14216, 0.69597, 1.5804, 1.4845, 0.23236, -0.38757, 0.96208, 0.95058, 0.90414, 0.91164, -0.99671, 0.76166, 0.24562, -0.4903, -1.0447, 1.1189, -0.64039, -0.69111, 0.72488, 1.3318, 0.37449, 0.81202, -0.73749, 1.5634, 0.43213, 0.75734, -1.638, 1.0798, 0.92385, -0.91116, 0.39467, -0.11789, 0.44525, 0.082613, 0.12463, -0.61588, -0.33664, -1.9424, 1.4365, 0.696, 1.4717, -0.69137, 1.4266, 1.0412, 0.5178, 0.18793, -0.3292, 0.93212, -0.42938, -1.3142, 0.97075, 0.73717, 0.84211, 0.66873, 0.13477, 0.061282, 1.0985, -0.14243, 1.0942, 1.0266, 1.2004, 0.34841, 0.65376, 1.5512, 0.19777, -1.3545, 1.2437, 0.64331, -0.035122, 1.8904, -0.44569, 0.69307, 0.5822, 0.051979, -0.79329, -1.8385, 0.14005, -0.60175, 0.86772, 0.0067388, 1.1693, 0.88836, 0.50291, -0.63243, 1.5826, -0.30375, 1.4399, -0.44715, 0.015393, -1.1216, 0.66418, -0.61639, -1.5213, 0.86139, -0.056376, 0.71224, 0.043007, 0.63434, -1.9155, 1.3878, 1.0567, 0.91698, 1.0903, 0.04151, 0.61085, 0.51336, 0.40654, -0.27221, -0.35949, 0.21689, -0.43283, 1.0671, 1.7634, -1.7453, 0.41981, -1.1247, 1.0608, 1.7911, -1.2887, 1.4999, -2.0038, 0.76706, 1.0127, 0.4162, 1.3021, 1.3474, 0.63105, -0.81528, -0.46915, -0.60996, -1.5634, -0.9903, 0.6089, 1.5011, -0.036833, 0.11313, 1.7488, 1.5269, 0.75003, 1.7831, 0.96949, -0.086687, 0.71639, -0.37479, -0.20822, 0.75839, 0.40131, 0.11562, 0.57671, 0.92857, 0.53214, 0.45782, 0.53223, 0.3632, -1.1584, 0.85265, 1.8759, -0.036615, 1.6585, -0.059146, 1.306, 0.22447, 0.12035, -0.4694, -0.88043, -0.16766, 0.86852};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_TRUE(instanceof_ptr<GEV_Distribution>(res));

	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 0., 1e-1);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 1., 1e-1);
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), -0.5, 1e-1);

}


TEST_F(EstimatorMLE_Test, EVT_0_1_P05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{2.04238, 1.30775, -1.07003, 2.84309, 5.0338, 1.92137, -0.873931, 0.0282173, 1.37823, 1.56135, -0.364209, -0.254483, 1.17835, 0.326199, 0.910929, -0.334513, -0.479826, 2.62795, 1.88243, 5.68283, -0.659695, -0.467196, -0.684573, 0.367184, -0.440066, 4.03199, -0.684589, -0.867688, 0.615641, 1.93651, -0.146991, -0.475221, -0.0771772, -0.398695, 0.437854, 4.37856, 0.936908, -0.677601, 0.06348, -0.827059, 0.406698, 0.182211, 38.467, 2.37746, 0.353326, 3.98822, -0.580021, 0.0610936, 5.28272, 4.81561, 1.44281, 0.884586, -0.065791, 5.77847, -0.613666, 1.56967, 1.02816, 2.68114, 0.0844709, 1.7273, 2.71327, -0.120034, 0.595579, 11.7713, 0.583938, -0.0994395, 0.890099, -0.0195928, 1.78614, 0.129433, 0.375948, 1.314, 10.0288, -0.10636, 2.7542, 1.63721, 7.23428, -0.922368, -0.0297111, 1.11777, -0.22362, -0.349311, 1.42543, 0.915169, 0.756061, 1.10516, -0.854028, -0.0512599, 0.242337, -0.323615, 1.45336, 3.07555, -0.223605, 1.5733, -0.579458, 2.73696, -0.577278, 0.745471, -0.00467716, 2.31603, 0.415406, 0.36661, 3.52173, -0.0396731, 0.236424, 8.3763, -0.875449, 10.0794, -0.449992, 1.14353, 0.737709, 1.19082, -0.0185548, 0.894035, 2.37164, -0.993672, -0.729601, 10.5193, 1.05456, -0.347225, 0.099339, -0.621039, -0.256005, -0.282101, -0.0962127, -0.542256, -0.0533201, -0.622012, 3.69976, -0.698525, 5.42643, 0.0865691, -0.854635, -0.068199, 1.61214, 2.17198, 0.566757, 1.25925, 3.9639, -0.826412, -0.16802, -0.85946, -0.43459, 1.49069, 1.50246, 3.53981, 0.720292, -0.771301, 5.05333, 2.23829, -0.212539, 0.561945, 14.1475, 1.45793, 2.773, 0.186849, 0.303734, 0.629428, -0.254392, 1.72038, 0.41578, 1.02994, -0.157665, -0.576959, 0.319887, -0.0146799, 2.09863, 2.01543, 1.15166, -0.590579, -0.978995, 0.625896, -0.175206, 5.99977, 12.4034, -0.210857, 2.24363, 4.03873, 0.78705, 3.6962, 6.31074, 0.583348, 1.55266, 0.695986, -0.953891, 0.227389, 1.02722, 0.477617, 0.0120874, 5.84898, 2.6263, 2.94475, 0.0126935, 0.767521, 3.41665, 5.62423, 1.15138, -0.406927, 1.06831, -0.766835};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 0., 1e-1);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 1., 1e-1);
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), 0.5, 1e-1);

}

TEST_F(EstimatorMLE_Test, EVT_0_1_0) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{1.5852, 2.3132, -0.72449, 2.4012, 0.78024, -0.84479, -0.24557, 0.50497, 3.1368, 3.3314, -0.61389, 3.5116, 3.1286, 0.32458, 1.5015, -0.66923, 0.14697, 2.4301, 1.457, 3.1857, 0.86277, -1.2037, 1.8107, 2.684, 0.94798, 1.2822, 1.2144, 0.066231, 0.86182, -0.56815, 1.0553, -1.2376, -0.24999, -1.1234, -0.84659, 1.6386, 1.0104, -0.13849, 2.9748, -1.2144, 0.19378, 0.037192, 1.3197, 1.4733, -0.5172, 0.33711, 0.21274, 0.82903, 1.0689, 1.2678, -0.25252, 0.95166, 0.86045, -0.59685, -0.75549, 0.3618, 3.192, -0.074807, 0.62421, -0.40343, 1.2518, -0.31197, 0.38375, 1.0272, 2.1583, 3.1806, 0.50598, -0.68107, -0.64282, -0.30506, 1.7516, -0.31431, 1.5826, -0.34539, 2.6123, -0.048665, -0.4865, -0.32351, 0.72477, 0.29029, -0.044105, 1.6856, 0.6242, 0.5136, 2.4483, -0.225, 1.2797, 1.2633, 0.034166, 0.56925, -0.94738, -1.0715, 0.45669, 1.3882, 2.6843, -0.71341, 0.57237, 0.27929, -1.4886, -0.083705, -0.59831, 1.4683, -0.15467, 0.44997, -0.58661, 0.6782, -0.28946, 0.85678, 0.98832, 1.2374, 0.22652, -0.90788, -0.38807, 2.4007, -0.63201, 1.6535, 0.47923, 5.5538, -0.93562, 0.20468, -0.80566, 3.2481, -1.6816, 1.3665, 1.6008, 1.9607, -0.90493, 0.086829, -0.2983, 1.5003, 0.17354, 2.3687, -0.53332, -0.2871, -0.65613, -0.69044, 1.9656, 0.60654, 0.51401, -0.65821, 1.8391, 0.74502, -0.046029, 0.40498, 0.092356, -0.9468, -0.3559, -0.73859, -0.52669, -0.35579, 0.13464, -1.0995, 2.2794, 2.8683, 0.34026, 0.33565, -0.082077, 2.2509, 0.0037168, -0.78682, 1.3938, 0.059454, -0.35072, 0.0981, -0.84959, -0.70565, 2.8185, 3.1043, 0.59236, -1.0357, -0.37095, -0.040026, 1.6246, -1.4287, -1.1461, -0.57544, 0.83899, 1.1636, 0.83412, 0.22758, 0.50536, -0.19582, 1.2215, -0.51057, 0.97884, -0.52797, 0.001645, 0.75712, 1.3936, -0.92098, 2.6141, 1.3705, 0.32862, 0.1858, 0.21607, -0.16808, 0.39116, 0.39775, 1.6027, 1.4713};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 0., 1e-1);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 1., 1e-1);
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), 0., 1e-1);

}


TEST_F(EstimatorMLE_Test, EVT_100_01_025) {

	constexpr int n_elem = 250;
	double xs[n_elem] =
	{100.029585858, 100.052490953, 99.9087113884, 100.097318955, 100.28401529, 99.9280435066, 100.019573272, 99.9766395309, 100.745589297, 100.076558958, 99.9696308853, 99.9355101332, 100.05317911, 100.206675747, 100.2158877, 100.212155041, 99.9561560434, 100.052978117, 100.261623515, 99.9318091534, 100.237418107, 100.301672301, 99.9600164646, 99.9160975329, 100.030389418, 100.213856252, 100.028928081, 100.012703412, 100.039253289, 99.9332398402, 99.9354069597, 100.255433286, 100.074284988, 99.9726931964, 100.247929784, 99.9079804403, 100.025440039, 100.129593102, 99.9922179768, 100.009178757, 100.047110036, 100.291772443, 100.165366099, 99.9129679674, 99.976257699, 100.003136147, 100.247762201, 100.014458203, 99.9659369821, 100.072239707, 100.031973421, 100.299421053, 100.38469746, 100.197370914, 100.122289746, 100.141948187, 100.301550075, 99.9111944467, 99.9913928678, 99.8619026979, 100.206958807, 100.040748443, 99.9995335401, 99.9623870903, 100.049728651, 99.9790836227, 99.9125450264, 99.9192170049, 99.9125316364, 100.011588475, 99.9325790735, 100.021098936, 100.30013623, 99.99614675, 99.9315419667, 100.061638355, 100.261750932, 99.9947843621, 99.8997283223, 99.9385143057, 99.9159427007, 100.140302867, 100.025074968, 100.102005438, 100.117206893, 100.062448393, 100.084623387, 100.2656704, 100.099282811, 100.262291356, 100.028362017, 99.9382078193, 99.9124442138, 100.125173882, 99.9839734919, 100.103369676, 100.094807617, 100.048462358, 100.125646938, 100.039910104, 100.03462371, 100.037700519, 100.38868104, 100.005863532, 99.9305495039, 99.9660828425, 100.109978793, 100.218230224, 100.558656683, 99.959284894, 100.15287662, 100.067120992, 100.009662604, 100.041584079, 100.037010286, 100.094341065, 100.142246782, 99.9823778361, 99.92096203, 100.204904362, 100.005947895, 100.163168668, 99.949369217, 99.9279516193, 100.311943759, 100.263629836, 102.932943333, 100.24722497, 99.8967744238, 100.053068709, 101.40972334, 100.041895473, 100.259612917, 99.913327735, 100.795334497, 100.351098, 100.059902448, 100.017749349, 99.9919093376, 100.128758337, 99.8778781461, 100.001683715, 100.351026648, 100.053684927, 100.030289604, 100.037290954, 99.9842342141, 100.444163206, 100.689472825, 100.042719975, 100.962069465, 100.024872764, 100.016192968, 99.9587532808, 99.9532641058, 100.211557518, 100.132109125, 100.048028179, 100.207919022, 100.042174627, 100.055578142, 99.9587723644, 100.068509288, 99.9386433941, 99.9051565753, 100.109193666, 100.07648042, 99.9605015929, 100.01059476, 100.085128547, 100.056743776, 99.9339218995, 99.9464634792, 99.8467269598, 100.013947401, 100.034774694, 99.9437522852, 100.101349611, 99.8824583433, 99.9313781705, 100.449926062, 100.611636216, 99.8929365326, 100.036457591, 100.245271296, 99.9667374513, 100.213086349, 100.193521733, 100.084739595, 99.8545015588, 100.003233218, 100.31046562, 100.107754517, 100.002986331, 100.085983577, 99.9668423661, 100.062468587, 100.685471802, 100.22962842, 99.9774883942, 100.108778301, 99.9973567994, 100.781002087, 99.9188409061, 99.9687159612, 100.191551138, 99.9190080515, 100.048530796, 100.1824965, 100.139272303, 99.938307743, 100.019608414, 99.995269636, 100.031695732, 100.068352898, 99.9395667952, 100.31228408, 100.089474713, 99.944649915, 100.060490884, 100.375351992, 100.168844572, 100.110362266, 100.027971396, 99.9713733625, 100.061694899, 99.9683076492, 99.9869721191, 100.323500761, 100.276927435, 100.177645244, 100.359128803, 99.9492192053, 100.044010908, 100.083924065, 100.328643306, 100.10002413, 100.005838983, 100.139988064, 100.19714223, 100.073275471, 99.9192270302, 100.350201285, 99.9058315227, 100.047125003, 99.931109732, 100.003348126, 100.192852618, 99.9670627154, 100.275682285};

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_location(), 100., 1e-0);	
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_scale(), 0.1, 1e-0);
	ASSERT_NEAR(std::dynamic_pointer_cast<GEV_Distribution>(res)->get_shape(), 0.25, 1e-0);

}


