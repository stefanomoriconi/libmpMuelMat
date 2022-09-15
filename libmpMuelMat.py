import os  # system library
import numpy as np  # for any numeric processing
import ctypes  # for interfacing with C-like data-types (pointers) used in the shared library
import time  # for computational performance
import matplotlib  # for plotting variables & results
import matplotlib.pyplot as plt
import scipy.io  # for matlab datasets
from datetime import datetime

__version__ = "1.0"

def credits():
    '''
    # Function to display the credits of libmpMuelMat library.
    '''

    print('-----------------------------------------------------------------------------')
    print(' libmpMuelMat: Open Library for Polarimetric Mueller Matrix Image Processing')
    print(' ')
    print(' version: 1.0 ')
    print(' requirements: Python 3.5+ -- https://www.python.org/downloads/ ')
    print('               GCC 9.4 or later -- https://gcc.gnu.org/ ')
    print('               openMP for parallel computing -- https://www.openmp.org/ ')
    print(' ')
    print(' readme and instructions: ./ReadMe.txt  -- please follow installation steps')
    print(' testing openMP: libmpMuelMat.test_OpenMP()')
    print(' ')
    print(' project: HORAO - Inselspital, Bern, CH -- 2022')
    print(' developer: Dr. Stefano Moriconi (stefano.nicola.moriconi@gmail.com)')
    print('-----------------------------------------------------------------------------')


def list_Dependencies():
    '''# Function to List all current dependencies of the libmpMuelMat library
	#
	# Please update any incorrect dependency prior to using the library. '''

    print(' ')
    print(' libmpMuelMat ', __version__, '-- list of dependencies:')
    print(' ')
    try:
        print(' * numpy (', np.__version__, ')')
    except:
        print(' * numpy ( NOT FOUND )')
    try:
        print(' * ctypes (', ctypes.__version__, ')')
    except:
        print(' * ctypes ( NOT FOUND )')
    try:
        print(' * matplotlib (', matplotlib.__version__, ')')
    except:
        print(' * matplotlib ( NOT FOUND )')
    try:
        print(' * scipy (', scipy.__version__, ')')
    except:
        print(' * scipy ( NOT FOUND )')
    print(' ')
    print(' C-libs shared library path:')
    if _chkFilePath(_get_CLib_path()):
        print(_get_CLib_path(), '-- FOUND')
    else:
        print(_get_CLib_path(), '-- NOT FOUND')
    print(' ')
    print(' Matlab (.mat) testing data path:')
    if _chkFilePath(_get_testDataMAT_path()):
        print(_get_testDataMAT_path(), ' -- FOUND')
    else:
        print(_get_testDataMAT_path(), ' -- NOT FOUND')
    print(' ')
    print(' ')
    print(' -- Please update any incorrect dependency prior to using the library.')
    print(' ')


def _get_CLib_path():
    '''
	# Function to retrieve the global (or local) path to the Compiled C Shared Library
	'''

    Clibs_pth = "./C-libs/libmpMuelMat.so"  # << Change the Global (or Local) path here if necessary!
    # Clibs_pth = "./C-libs/libmpMuelMat.dll" # << Uncomment and Change here for Windows OS

    return Clibs_pth


def _loadClib():
    '''
	# Function to retrieve the callable handle to the Compiled C Shared Library
	'''
    try:
        Clib = ctypes.cdll.LoadLibrary(_get_CLib_path())
    except:
        Clib = None
        print(
            " <!> libmpMuelMat: Cannot Load Shared Library! -- Please check dependencies with: libmpMuelMat.list_Dependencies()")

    return Clib


def _get_testDataMAT_path():
    '''
	# Function to retrieve the global (or local) path to test Data (MATLAB data format '.mat')
	'''
    testDataMAT_pth = './TestData/MAT/libmpMuelMat_TestData.mat'  # << Change here the path to the testing/validation data

    return testDataMAT_pth


def _get_test_calib_path(): # TO BE REMOVED
    '''
	# Private Function to retrieve the testing calibration folder path
	'''

    test_calib_path = './TestData/Raw/Calibration/'  # << Change here the path to the test calibration folder

    return test_calib_path


def _get_test_scan_path():
    '''
	# Private Function to retrieve the testing Raw Intensities folder path
	'''
    test_scan_path = './TestData/Raw/Scan/'  # << Change here the path to the test scan folder

    return test_scan_path


def _chkFilePath(filePath):
    '''
	# Private Function to check existence of a file in the computer
	'''

    return os.path.exists(filePath) & os.path.isfile(filePath)


def _chkFolderPath(folderPath):
    '''
	# Private Function to check the existence of a folder in the computer
	'''

    return os.path.exists(folderPath) & os.path.isdir(folderPath)


def default_CamType(CamID=None):
    '''# Define the Default Camera Type used in the Polarimetric Acquisitions
	# Default:  'Stingray IPM2'
	#
	# Call: CamType = default_CamType([CamID])
	#
	# *Inputs*
	# [CamID]: optional scalar integer identifying the Camera device as listed below
	#
	# *Outputs*
	# CamType: string with the camera device identifier
	#
	# Possible Options for different input CamID:
	#
	# CamID		CamType
	# 0 	-> 	'Stingray IPM2' (default)
	# 1 	-> 	'Prosilica'
	# 2 	-> 	'JAI'
	# 3 	-> 	'JAI Packing 2x2'
	# 4 	-> 	'JAI Binning'
	# 5 	-> 	'Stingray'
	# 6 	-> 	'Stingray IPM1'
	#
	# -1    ->  'TEST' -- used for (Unit)Testing
	'''

    CamType = None

    if (CamID == None):
        CamID = 0

    if (CamID == -1):
        CamType = 'TEST'
    if (CamID == 0):
        CamType = 'Stingray IPM2'
    if (CamID == 1):
        CamType = 'Prosilica'
    if (CamID == 2):
        CamType = 'JAI'
    if (CamID == 3):
        CamType = 'JAI Packing 2x2'
    if (CamID == 4):
        CamType = 'JAI Binning'
    if (CamID == 5):
        CamType = 'Stingray'
    if (CamID == 6):
        CamType = 'Stingray IPM1'
    if (int(CamID) < -1 | int(CamID) > 6):
        CamType = 'Stingray IPM2'  # Default

    return CamType


def get_Cam_Params(CamType):
    '''# Function to retrieve the polarimetric Camera Parameters
	# Several camera types are listed below
	#
	# Call: (ImgShape2D,GammaDynamic) = get_Cam_Params(CamType)
	#
	# *Inputs*
	# CamType: string identifying the camera type (see: default_CamType()).
	#
	# * Outputs *
	# ImgShape2D: list containing the camera pixel-wise size as [dim[0],dim[1]]
	# GammaDynamic: scalar intensity as maximum value for detecting saturation/reflection'''

    ImgShape2D = None
    GammaDynamic = None

    if (CamType == 'Prosilica'):
        GammaDynamic = 16384
        ImgShape2D = [600, 800]

    if (CamType == 'JAI'):
        GammaDynamic = 16384
        ImgShape2D = [768, 1024]

    if (CamType == 'JAI Packing 2x2'):
        GammaDynamic = 16384
        ImgShape2D = [384, 512]

    if (CamType == 'JAI Binning'):
        GammaDynamic = 16384
        ImgShape2D = [384, 1024]

    if (CamType == 'Stingray'):
        GammaDynamic = 65530
        ImgShape2D = [600, 800]

    if (CamType == 'Stingray IPM1'):
        GammaDynamic = 65530
        ImgShape2D = [388, 516]

    if (CamType == 'Stingray IPM2'):
        GammaDynamic = 65530
        ImgShape2D = [388, 516]

    if (CamType == 'TEST'):
        GammaDynamic = 65530
        ImgShape2D = [128, 128]

    return ImgShape2D, GammaDynamic


def get_testDataMAT():
    '''# Function to retrieve variables from the MATLAB test Data
	# The loaded variables are:
	# A,W: polarisation states matrices obtained from calibration to compute the Mueller Matrix
	# I: intensities (background noise is subtracted) to compute the Mueller Matrix
	# IN: raw intensities
	#
	# NB: as the variables are natively from a MATLAB environment (fortran ordering),
	#     the data is re-ordered in a C-like fashion in line with subsequent processing.
	#
	# Variables are returned in the following order: A,I,W,IN'''

    mat = scipy.io.loadmat(_get_testDataMAT_path())

    A = mat.get('A')
    I = mat.get('INTENSITE')
    W = mat.get('W')
    IN = mat.get('IN')

    if np.isfortran(A):
        A = A.ravel(order='C').reshape(A.shape)

    if np.isfortran(I):
        I = I.ravel(order='C').reshape(I.shape)

    if np.isfortran(W):
        W = W.ravel(order='C').reshape(W.shape)

    if np.isfortran(IN):
        IN = IN.ravel(order='C').reshape(IN.shape)

    return A, I, W, IN


def _get_validDataMAT():
    '''
	# Provate Function to retrieve validation variables from the MATLAB test Data
	# The loaded variables are considered as Reference in the validation and are the following:
	#
	# Call: validDataMAT = _get_validDataMAT()
	#
	# validDataMAT: dictionary containing the following keys:
	#
	# 'nM': (normalised) Mueller Matrix
	# 'M11': normalising Mueller Matrix Component M(1,1)
	#
	# 'Mdetmsk': mask of the pixels with negative M determinant
	# 'Mphymsk': mask of the pixels satisfying the physical criterion
	# 'Isatmsk': mask of the pixels with saturated intensities (e.g. reflections)
	# 'Msk': final mask of the valid pixels obtained as logical AND of the above ones
	#
	# 'Els': Real part of the Mueller Matrix EigenValues (unsorted)
	# 'Elsmsk': mask of the negative EigenValues per lambda (sorted)
	#
	# 'MD': polarimetric matrix of diattenuation
	# 'MR': polarimetric matrix of phase shift (retardance)
	# 'Mdelta': polarimetric matrix of depolarisation
	#
	# 'totD': total diattenuation
	# 'linD': linear diattenuation
	# 'cirD': circular diattenuation
	# 'oriD': orientation of linear diattenuation
	#
	# 'totR': total phase shift (retardance)
	# 'linR': linear phase shift (retardance)
	# 'cirR': circular phase shift (retardance)
	# 'oriR': orientation of linear phase shift (retardance)
	# 'oriRfull': full orientation of linear phase shift (retardance)
	#
	# 'totP': total depolarisation
	#
	# Variables are returned in the order above.
	'''

    mat = scipy.io.loadmat(_get_testDataMAT_path())

    validDataMAT = {'nM': mat.get('MM'),
                    'M11': mat.get('M11'),
                    'Mdetmsk': mat.get('mask_det_neg'),
                    'Mphymsk': mat.get('mask_physical_criterion'),
                    'Isatmsk': mat.get('mask_saturation'),
                    'Msk': mat.get('mask_final'),
                    'Els': mat.get('Image_eigenvalues_coherency'),
                    'MD': mat.get('Image_MD'),
                    'MR': mat.get('Image_MR'),
                    'Mdelta': mat.get('Image_Mdelta'),
                    'totD': mat.get('Image_total_diattenuation'),
                    'linD': mat.get('Image_linear_diattenuation'),
                    'cirD': mat.get('Image_circular_diattenuation'),
                    'oriD': mat.get('Image_orientation_linear_diattenuation'),
                    'totR': mat.get('Image_total_retardance'),
                    'linR': mat.get('Image_linear_retardance'),
                    'cirR': mat.get('Image_circular_retardance'),
                    'oriR': mat.get('Image_orientation_linear_retardance'),
                    'oriRfull': mat.get('Image_orientation_linear_retardance_full'),
                    'totP': mat.get('Image_total_depolarization')}

    return validDataMAT


def read_cod_data_X3D(input_cod_Filename, CamType=None, isRawFlag=0, VerboseFlag=0):
    '''# Function to read (load) stacked 3D data from the camera acquisition or other exported dataset in '.cod' binary format.
	# The data can be calibration data, intensity data (and background noise), or processed data with the libmpMuelMat library.
	#
	# Call: X3D = read_cod_data_X3D( input_cod_Filename, [CamType] , [isRawFlag] , [VerboseFlag] )
	#
	# *Inputs*
	# input_cod_Filename: string with Global (or local) path to the '.cod' file to import.
	#
	# [CamType]: optional string with the Camera Device Name used during the acquisition (see: default_CamType())
	#
	# [isRawFlag]: scalar boolean (0,1) as flag for Raw data (e.g. raw intensities and calibration data) -- default: 0
	#              if 1 -> '.cod' interpreted *with Header* and *Fortran-like ordering*
	#              if 0 -> '.cod' interpreted *without Header* and native *C-like ordering*
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
 	#
	# * Outputs *
	# X3D: 3D stack of Polarimetric Components of shape shp3 = [dim[0],dim[1],16].
	# 	   NB: the dimensions dim[0] and dim[1] are given by the camera parameters from CamType.
	'''

    if (CamType == None):
        CamType = default_CamType()  # << default

    shp2 = get_Cam_Params(CamType)[0]

    ## Initial Time (Total Performance)
    t = time.time()

    header_size = 140  # header size of the '.cod' file
    m = 16  # components of the polarimetric data in the '.cod' file

    # Reading the Data (loading) NB: binary data is float, but the output array is *cast* to double
    with open(input_cod_Filename, "rb") as f:
        X3D = np.fromfile(f, dtype=np.single).astype(np.double)
        f.close()

    if isRawFlag:
        # Calibration files WITH HEADER (to be discarded)
        # Reshaping and transposing the shape of the imported array (from Fortran- -> C-like)
        X3D = np.moveaxis(X3D[header_size:].reshape([shp2[1], shp2[0], m]), 0, 1)
    else:
        # Other Files from libmpMuelMat processing WITHOUT HEADER
        # Reshaping the imported array (already C-like)
        X3D = X3D.reshape([shp2[0], shp2[1], m])

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> read_cod_data_X3D Performance: Elapsed time = {:.3f} s'.format(telaps))

    return X3D


def write_cod_data_X3D(X3D, output_cod_Filename, VerboseFlag=1):
    '''# Function to write (export) stacked 3D data from the camera acquisitions or further processing in '.cod' binary format.
	# The data can be both calibration data (A,W), or processed intensities(I), or processed 3D data (MM), etc.
	#
	# Call: write_cod_data_X3D( X3D, output_cod_Filename, [VerboseFlag] )
	#
	# *Inputs*
	# X3D: 3D stack of images, e.g. calibration states (A,W), processed intensities, polarimetric components ...
	#      X3D is expected to be of shape shp3 = [dim[0],dim[1],16].
	#
	# output_cod_Filename: string with Global (or local) path to export the data in binary format with '.cod' extension.
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 1)
 	#
 	# NB: The output data array will be written in C-like ordering.
	'''

    shp3 = X3D.shape
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "X3D" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "X3D" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    with open(output_cod_Filename, "wb") as f:
        X3D.astype(np.single).tofile(f)
        f.close()

    if VerboseFlag:
        print(' ')
        print(' >> Exported X3D .cod file as:', output_cod_Filename)

    return None


def read_cod_data_X2D(input_cod_Filename, CamType=None, VerboseFlag=0):
    '''# Function to read (load) 2D data from exported dataset in '.cod' binary format.
	# The 2D data is a component of processed data using the libmpMuelMat library.
	#
	# Call: X2D = read_cod_data_X2D( input_cod_Filename, [CamType] , [VerboseFlag] )
	#
	# *Inputs*
	# input_cod_Filename: string with Global (or local) path to the '.cod' file to import.
	#
	# [CamType]: optional string with the Camera Device Name used during the acquisition (see: default_CamType())
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
 	#
	# * Outputs *
	# X2D: 2D Component (e.g. a polarimetric feature) processed with libmpMuelMat of shape shp2 = [dim[0],dim[1]].
	# 	   NB: the dimensions dim[0] and dim[1] are given by the camera parameters.
	'''

    if (CamType == None):
        CamType = default_CamType()  # << default

    shp2 = get_Cam_Params(CamType)[0]

    ## Initial Time (Total Performance)
    t = time.time()

    # Reading the Data (loading) NB: binary data is float, but the output array is *cast* to double
    with open(input_cod_Filename, "rb") as f:
        X2D = np.fromfile(f, dtype=np.single).astype(np.double)
        f.close()

    # Reshaping the imported array (already C-like)
    X2D = X2D.reshape(shp2)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> read_cod_data_X2D Performance: Elapsed time = {:.3f} s'.format(telaps))

    return X2D


def write_cod_data_X2D(X2D, output_cod_Filename, VerboseFlag=1):
    '''# Function to write (export) 2D data from the camera acquisitions or further processing in '.cod' binary format.
	# The data is usually a 2D Component of a Polarimetric feature processed with libmpMuelMat library.
	#
	# Call: write_cod_data_X2D( X2D, output_cod_Filename, [VerboseFlag] )
	#
	# *Inputs*
	# X2D: 2D Component (e.g. a polarimetric feature) processed with libmpMuelMat of shape shp2 = [dim[0],dim[1]].
	#
	# output_cod_Filename: string with Global (or local) path to export the data in binary format with '.cod' extension.
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 1)
 	#
 	# NB: The output data array will be written in C-like ordering.
	'''

    shp2 = X2D.shape
    if (np.prod(np.shape(shp2)) != 2):
        raise Exception(
            'Input: "X2D" should have shape of a 2D image, e.g. (idx0, idx1). The shape value was found: {}'.format(
                shp2))

    with open(output_cod_Filename, "wb") as f:
        X2D.astype(np.single).tofile(f)
        f.close()

    if VerboseFlag:
        print(' ')
        print(' >> Exported X2D .cod file as:', output_cod_Filename)

    return None


def _gen_AIW_rnd(shp2=None):
    '''# Function to generate random A, I, and W, as in Mueller Matrix computation M = AIW.
	#
	# Call: (A,I,W) = gen_AIW_rnd( shp2 )
	#
	# *Inputs*
	# shp2: shape of the 2D A, I, and W images as (dim0, dim1)
	# 		NB: is shp2 is not provided, a default shape is retrieved, based on default camera type.
	#
	# *Outputs*
	# A: 3D arrays of shape [shp2[0],shp2[1],16] with random values.
	#
	# I: 3D arrays of shape [shp2[0],shp2[1],16] with random values.
	#
	# W: 3D arrays of shape [shp2[0],shp2[1],16] with random values.
	#
	# The output values follow a canonical normal distribution (mean=0,std=1).
	#
	#
	# Note:
	# In later stages, this function may embed a generative functionality based on Diffusion Networks
	# to synthesise new samples of Intensities (as well as polarisation states A,W) from random noise.'''

    if (shp2 == None):
        shp2 = get_Cam_Params(default_CamType())[0]

    # Checking Inputs
    if np.prod(np.shape(shp2)) != 2:
        raise Exception(
            'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                shp2))
    if ~ np.all(np.isfinite(shp2), axis=-1):
        raise Exception('Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
    if ~ np.all(shp2 == np.array(shp2, np.int32)):
        shp2 = np.array(shp2, np.int32)
        print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
    if ~ np.all(np.greater(shp2, 0)):
        raise Exception('Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    # Determining outputs
    A = np.random.randn(shp2[0], shp2[1], 16)
    I = np.random.randn(shp2[0], shp2[1], 16)
    W = np.random.randn(shp2[0], shp2[1], 16)

    return A, I, W


def gen_AW(shp2=None, wlen=550):
    '''#Function to generate synthetic polarisation state/acquisition matrices A,W of arbitrary shape.
	# The polarisation matrices A,W can be used to compute the Mueller Matrix decomposition,
	# given an input set of intensities I.
	#
	# Call: (A,W) = gen_AW([shp2],[wlen])
	#
	# *Inputs*
	# shp2: shape of the 2D A, I, and W images as (dim0, dim1)
	# 		NB: is shp2 is not provided, a default shape is retrieved, based on default camera type.
	#
	# wlen: integer scalar for the polarimetric wavelength in nm [default: 550]
	#		supported wavelengths: [550, 650]
	#
	# *Outputs*
	#
	# A,W: 3D arrays of shape [shp2[0],shp2[1],16] with values from previous calibrations.
	#      NB: the values are statistical estimations, and should be used in synthetic set-up only,
	#          in order to simulate an artificial calibration of the system.
	#
	# NB: only 2 wavelength are currently supported: 550nm (default) and 650nm
	#     other input wavelengths will produce randomly distributed (Gaussian) matrices as output.
	'''

    if (shp2 == None):
        shp2 = get_Cam_Params(default_CamType())[0]
    else:
        if np.prod(np.shape(shp2)) != 2:
            raise Exception(
                'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                    shp2))
        if ~ np.all(np.isfinite(shp2), axis=-1):
            raise Exception(
                'Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
        if ~ np.all(shp2 == np.array(shp2, np.int32)):
            shp2 = np.array(shp2, np.int32)
            print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
        if ~ np.all(np.greater(shp2, 0)):
            raise Exception(
                'Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    if (wlen == None):
        wlen = 550

    shp3 = [shp2[0], shp2[1], 1]

    if wlen == 550:  # 550nm case
        Aavg = np.reshape([1.0, 1.0067, 1.0063, 1.0103,
                           -0.7548, 0.5901, 0.0144, -0.1166,
                           0.6439, -0.5866, 0.2537, -0.7111,
                           0.1301, 0.5103, -0.9442, -0.6459], [1, 1, 16])

        Asd0 = np.reshape([0.0, 0.0023, 0.0008, 0.0037,
                           0.0029, 0.0034, 0.0038, 0.0066,
                           0.0118, 0.0104, 0.0112, 0.0072,
                           0.0039, 0.0075, 0.0030, 0.0040], [1, 1, 16])

        Asd1 = np.reshape([0.0, 0.1616, 0.1144, 0.1749,
                           0.3796, 0.7578, 0.3512, 0.4703,
                           0.9391, 0.6024, 0.6473, 0.6591,
                           0.6314, 0.4556, 0.5217, 0.3556], [1, 1, 16]) * 1e-3

        Wavg = np.reshape([1.0, 0.4459, -0.3686, 0.0157,
                           0.9764, -0.2924, 0.3592, 0.3089,
                           0.9910, -0.1115, -0.1771, -0.4991,
                           0.9927, 0.1199, 0.4264, -0.3359], [1, 1, 16])

        Wsd0 = np.reshape([0.0, 0.0153, 0.0189, 0.0054,
                           0.0045, 0.0161, 0.0110, 0.0144,
                           0.0018, 0.0073, 0.0085, 0.0218,
                           0.0044, 0.0032, 0.0203, 0.0116], [1, 1, 16])

        Wsd1 = np.reshape([0.0, 0.5660, 0.4860, 0.2746,
                           0.2612, 0.3685, 0.4690, 0.3205,
                           0.1963, 0.4282, 0.4011, 0.4667,
                           0.3608, 0.2955, 0.6957, 0.3378], [1, 1, 16]) * 1e-3

        A = np.tile(Aavg, shp3) + \
            np.tile(Asd0 * np.random.randn(1, 1, 16), shp3) + \
            np.tile(Asd1, shp3) * np.random.randn(shp3[0], shp3[1], shp3[2])

        W = np.tile(Wavg, shp3) + \
            np.tile(Wsd0 * np.random.randn(1, 1, 16), shp3) + \
            np.tile(Wsd1, shp3) * np.random.randn(shp3[0], shp3[1], shp3[2])

    elif wlen == 650:  # 650nm case

        Aavg = np.reshape([1.0, 1.0043, 1.0109, 0.9891,
                           -0.8740, 0.4763, -0.1336, -0.1286,
                           0.4076, -0.5499, 0.0573, -0.9903,
                           -0.0872, 0.7152, -0.9581, -0.2042], [1, 1, 16])

        Asd0 = np.reshape([0.0, 0.0019, 0.0013, 0.0046,
                           0.0014, 0.0124, 0.0054, 0.0151,
                           0.0120, 0.0066, 0.0118, 0.0089,
                           0.0021, 0.0069, 0.0025, 0.0082], [1, 1, 16])

        Asd1 = np.reshape([0.0, 0.0003, 0.0001, 0.0003,
                           0.0004, 0.0012, 0.0009, 0.0005,
                           0.0017, 0.0013, 0.0012, 0.0016,
                           0.0009, 0.0010, 0.0025, 0.0016], [1, 1, 16])

        Wavg = np.reshape([1.0, 0.3281, -0.1997, -0.0830,
                           1.0085, -0.1275, 0.2055, 0.2813,
                           1.0031, -0.0071, -0.1106, -0.3519,
                           1.0254, 0.0806, 0.3605, -0.0691], [1, 1, 16])

        Wsd0 = np.reshape([0.1, 0.0198, 0.0123, 0.0076,
                           0.0042, 0.0142, 0.0085, 0.0200,
                           0.0018, 0.0064, 0.0097, 0.0236,
                           0.0047, 0.0053, 0.0218, 0.0021], [1, 1, 16])

        Wsd1 = np.reshape([0.0, 0.0008, 0.0006, 0.0003,
                           0.0006, 0.0003, 0.0009, 0.0009,
                           0.0002, 0.0010, 0.0010, 0.0007,
                           0.0009, 0.0004, 0.0010, 0.0002], [1, 1, 16])

        A = np.tile(Aavg, shp3) + \
            np.tile(Asd0 * np.random.randn(1, 1, 16), shp3) + \
            np.tile(Asd1, shp3) * np.random.randn(shp3[0], shp3[1], shp3[2])

        W = np.tile(Wavg, shp3) + \
            np.tile(Wsd0 * np.random.randn(1, 1, 16), shp3) + \
            np.tile(Wsd1, shp3) * np.random.randn(shp3[0], shp3[1], shp3[2])

    else:
        print(' <!> gen_AW: parsed wavelength is not supported: returning random as in "gen_AIW_rnd"')
        A = np.random.randn(shp2[0], shp2[1], 16)
        W = np.random.randn(shp2[0], shp2[1], 16)

    return A, W


def map_msk2_to_idx(msk2):
    '''# Function to determine the C-like linear indices, given a logical mask of a 2D image.
	#
	# Call: idx = map_msk2_to_idx( msk2 )
	#
	# *Inputs*
	# msk2: boolean mask of a 2D image of shape (dim0, dim1)
	#
	# *Outputs*
	# idx: C-like linear indices corresponding to the 'True' voxels in msk2
	#	e.g. if msk3 has shape (3,3) and the only true value is in the middle,
	#	i.e. msk2[1,1] = True, the idx array will be a scalar equal to 4.
	#   NB: indexing starts from 0
	'''

    # Checking Inputs
    if np.prod(np.shape(np.shape(msk2))) != 2:
        raise Exception(
            'Input: "msk2" should have the shape of a 2D image, e.g. (idx0, idx1). The shape was: {}'.format(
                np.shape(msk2)))
    if msk2.dtype != bool:
        raise Exception('Input: "msk2" should be logical, i.e. boolean type. The data type was: {}'.format(msk2.dtype))

    idx = np.array(np.ravel_multi_index(np.nonzero(msk2), msk2.shape), dtype=np.int32)

    return idx


def _mng_Idxs(idx, shp2):
    '''
	# Function to manage indexing of pixels array to be processed in the Mueller Matrix computing.
	# This function is meant to harmonise indices values compatibly with a C-compiled shared library.
	#
	# Call: (idx,idx_ptr,numel,numel_ptr) = _mng_Idxs( idx,shp2 )
	#
	# *Inputs*
	# idx: scalar value identically equal to -1 (negative one)     *OR*
	#	   1D array containing unique C-like indices of selected pixel array locations within the 2D image [dim[0],dim[1]].
	#
	# shp2: shape of the 2D image: expected [dim[0],dim[1]]
	#
	# *Outputs*
	# idx: updated 1D array containing unique C-like indices of
	#	   *ALL* or *SELECTED* pixel locations within the 2D image.
	# idx_ptr: C-like pointer to the 1D updated array of indices (idx)
	# numel: scalar number of elements in the updated 1D array of indices (idx)
	# numel_ptr: C-like pointer to the scalar number of elements (numel)
	'''

    # Checking Inputs
    if np.prod(np.shape(shp2)) != 2:
        raise Exception(
            'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                shp2))
    if ~ np.all(np.isfinite(shp2), axis=-1):
        raise Exception('Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
    if ~ np.all(shp2 == np.array(shp2, np.int32)):
        shp2 = np.array(shp2, np.int32)
        print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
    if ~ np.all(np.greater(shp2, 0)):
        raise Exception('Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    # Remove possible repetitions
    idx = np.unique(np.array(idx))

    if (np.prod(np.shape(idx)) == 1) & np.all(idx == -1):
        # CASE: process *ALL* voxels in the 3D image

        numel = np.array(np.prod(shp2), dtype=np.int32)  # IMPORTANT: data type must be int32
        numel_ptr = numel.ctypes.data_as(ctypes.POINTER(ctypes.c_int))

        idx = np.array(np.arange(0, numel), dtype=np.int32)  # IMPORTANT: data type must be int32
        idx_ptr = idx.ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    else:
        # CASE: process *SELECTED* voxels in the 3D image

        # Checking that the selected voxel indices are within the 3D image shape range
        if not (np.all(np.greater_equal(idx, 0)) & np.all(np.less(idx, np.prod(shp2)))):
            raise Exception('The parsed indices (idx) are *OUT* of the 3D image. The parsed idx is: {}'.format(idx))

        idx = np.array(idx, dtype=np.int32)  # IMPORTANT: data type must be int32
        idx_ptr = idx.ctypes.data_as(ctypes.POINTER(ctypes.c_int))

        numel = np.array(np.prod(idx.shape), dtype=np.int32)  # IMPORTANT: data type must be int32
        numel_ptr = numel.ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    return idx, idx_ptr, numel, numel_ptr


def ini_MM(shp2):
    '''# Function to initialise the Mueller Matrix Components used in the compiled Shared Library
	# This function set the data type to double (i.e. np.double).
	#
	# Call: (M,M_ptr) = ini_MM( shp2 )
	#
	# *Inputs*
	# shp2: shape of the 2D Mueller Matrix image as (dim0, dim1)
	#
	# *Outputs*
	# M: Mueller Matrix of shape (shp2[0],shp2[1],16) initialised as zeros
	# M_ptr: C-like pointer to the Matrix '''

    # Checking Inputs
    if np.prod(np.shape(shp2)) != 2:
        raise Exception(
            'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                shp2))
    if ~ np.all(np.isfinite(shp2), axis=-1):
        raise Exception('Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
    if ~ np.all(shp2 == np.array(shp2, np.int32)):
        shp2 = np.array(shp2, np.int32)
        print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
    if ~ np.all(np.greater(shp2, 0)):
        raise Exception('Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    # Initialising Outputs
    M = np.zeros([shp2[0], shp2[1], 16], dtype=np.double)
    M_ptr = _ptr_X(M)

    return M, M_ptr


def ini_Comp(shp2):
    '''# Function to initialise a 2D Component (can be used in C compiled code with pointer)
	# This function set the data type to double (i.e. np.double).
	#
	# Call: (X2D,X2D_ptr) = ini_Comp( shp2 )
	#
	# *Inputs*
	# shp2: shape of the 2D image Component as (dim0, dim1)
	#
	# *Outputs*
	# X2D: 2D Image Component of shape (shp2[0],shp2[1]) initialised as zeros'''

    X2D = np.zeros(shp2, dtype=np.double)
    X2D_ptr = X2D.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    return X2D, X2D_ptr


def ini_msk2(shp2):
    '''# Function to initialise the logical mask variable (can be used in the compiled Shared Library with the pointer)
	# This function set the data type to boolean, and returns the associated pointer.
	#
	# Call: (msk2,msk2_ptr) = ini_msk2( shp2 )
	#
	# *Inputs*
	# shp2: shape of the 2D image as (dim0, dim1)
	#
	# *Outputs*
	# msk2: logical validity mask of 2D shape (shp2), initialised as 'True'
	# msk2_ptr: pointer of the logical validity mask.'''

    if np.prod(np.shape(shp2)) != 2:
        raise Exception(
            'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                shp2))
    if ~ np.all(np.isfinite(shp2), axis=-1):
        raise Exception('Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
    if ~ np.all(shp2 == np.array(shp2, np.int32)):
        shp2 = np.array(shp2, np.int32)
        print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
    if ~ np.all(np.greater(shp2, 0)):
        raise Exception('Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    msk2 = np.ones(shp2, dtype=np.bool_)
    msk2_ptr = msk2.ctypes.data_as(ctypes.POINTER(ctypes.c_bool))

    return msk2, msk2_ptr


def ini_REls(shp2):
    '''# Function to initialise the REAL EigenVALUES of the Mueller Matrix for the compiled Shared Library
	# This function set the data type to double (i.e. np.double).
	#
	# Call: (REls,REls_ptr) = ini_REls( shp2 )
	#
	# *Inputs*
	# shp2: shape of the 2D Mueller Matrix REAL EigenValue Component as (dim0, dim1)
	#
	# *Outputs*
	# REls: REAL EigenVALUES of the Mueller Matrix of shape (shp2[0],shp2[1],4) initialised as zeros
	# REls_ptr: C-like pointer to the variable'''

    # Checking Inputs
    if np.prod(np.shape(shp2)) != 2:
        raise Exception(
            'Input: "shp2" should be the shape of a 2D image, e.g. (idx0, idx1). The value of "shp2" was: {}'.format(
                shp2))
    if ~ np.all(np.isfinite(shp2), axis=-1):
        raise Exception('Input: "shp2" should contain all FINITE elements. The value of "shp2" was: {}'.format(shp2))
    if ~ np.all(shp2 == np.array(shp2, np.int32)):
        shp2 = np.array(shp2, np.int32)
        print(" -- Warning: Input argument (shp2) has non-integer elements - Default: round to closest integers.")
    if ~ np.all(np.greater(shp2, 0)):
        raise Exception('Input: "shp2" has non-positive number of elements. The value of "shp2" is: {}'.format(shp2))

    # Initialising Outputs
    REls = np.zeros([shp2[0], shp2[1], 4], dtype=np.double)
    REls_ptr = _ptr_X(REls)

    return REls, REls_ptr


def _ptr_X(X):
    '''
	# Private Function to determine the pointers to the Matrix Components variables used in the compiled Shared Library
	#
	# Call: X_ptr = _ptr_X( X )
	#
	# *Inputs*
	# X: any numpy NDarray
	#
	# *Outputs*
	# X_ptr: C-like pointer to the input X
	'''

    X_ptr = X.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    return X_ptr


def compute_MM_AIW(A, I, W, idx=-1, VerboseFlag=0):
    '''# Function to compute the Mueller Matrix from the equation M = AIW
	#
	# Call: (M,nM) = compute_MM_AIW_new( A , I , W , [idx] , [VerboseFlag] )
	#
	# *Inputs*
	# A, I, W:
	# 	stacked 3D arrays with 16 components in the last dimension.
	# 	All A, I, amd W must have the same shape: shp3 = A.shape,
	# 	corresponding to a 3D stack of 2D images in the form shp3 = [dim[0],dim[1],16].
	#
	#   >> NB: all A,I,W should have a c-like ordering (not fortran-like ordering) for best performance!
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices are considered (default),
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# * Outputs *
	# M: 3D stack of Mueller Matrix Components of shape shp3.
	# 	The matrix has the form [dim[0],dim[1],16].
	#
	# nM: 3D stack of normalised Mueller Matrix Components of shape shp3 = [dim[0],dim[1],16].
	#	  Each Component is normalised by M(1,1) as default.
	#
	# *** This is a python wrapper for the shared library: libmpMuelMat.so ***
	# *** The C-compiled shared library automatically enables and configures
	# *** multi-core processing for maximal performance using OpenMP libraries.'''

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    ## Initial Time (Total Performance)
    t = time.time()

    # Retrieving 3D image shape
    shp3 = np.shape(A)
    shp2 = [shp3[0], shp3[1]]

    # Managing voxel indices and pointers
    (idx, idx_ptr,
     numel, numel_ptr) = _mng_Idxs(idx, shp2)

    # Determining Input Pointers
    A_ptr = _ptr_X(A.ravel(order='C'))

    # Determining Input Pointers
    I_ptr = _ptr_X(I.ravel(order='C'))

    # Determining Input Pointers
    W_ptr = _ptr_X(W.ravel(order='C'))

    # Initialising M Output
    (M, M_ptr) = ini_MM(shp2)
    (nM, nM_ptr) = ini_MM(shp2)

    # Calling the C-compiled function from the shared library
    mpMuelMatlibs.mp_comp_MM_AIW(M_ptr, nM_ptr,
                                 A_ptr, I_ptr, W_ptr,
                                 idx_ptr, numel_ptr)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> compute_MM_AIW Performance: Elapsed time = {:.3f} s'.format(telaps))

    return M, nM


def norm_MM(M):
    '''# Function to normalise the Mueller Matrix coefficients by the first one (M11)
	#
	# Call: (nM,M11) = norm_MM( M )
	#
	# *Inputs*
	# M: 3D stack of Mueller Matrix Components of shape shp3.
	# 	The matrix has the form [dim[0],dim[1],16].
	#
	# * Outputs *
	# nM:  normalised 3D stack of Mueller Matrix Components of shape shp3.
	# M11: 2D normalising coefficient (shape: [dim[0],dim[1]] )of the Mueller Matrix'''

    shp3 = np.shape(M)
    shp2 = [shp3[0], shp3[1]]
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "M" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "M" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    (nM, _) = ini_MM(shp2)
    M11 = np.array(M[:, :, 0])

    # Element-wise normalisation
    for i in range(shp3[-1]):
        nM[:, :, i] = np.divide(M[:, :, i], M11)

    # Returning Normalised Tensor and Normalising Component M11 (reference)
    return nM, M11


def compute_MM_det(M, idx=-1, VerboseFlag=0):
    '''# Function to compute the determinant of the Mueller Matrix
	#
	# Call: (Mdet,MdetMsk) = compute_MM_det( M , [idx] , [VerboseFlag] )
	#
	# *Inputs*
	# M: 3D stack of Mueller Matrix Components of shape shp3.
	# 	The matrix has the form [dim[0],dim[1],16].
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# * Outputs *
	# Mdet: final Mueller Matrix determinant image of shape [dim[0],dim[1]],
	# MdetMsk: boolean Mask of validity for the Determinant of the Mueller Matrix
	#		   MdetMsk = Mdet > 0   (default)
	#
	# *** This is a python wrapper for the shared library: libmpMuelMat.so ***
	# *** The C-compiled shared library automatically enables and configures
	# *** multi-core processing for maximal performance using OpenMP libraries.'''

    shp3 = np.shape(M)
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "M" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "M" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    ## Initial Time (Total Performance)
    t = time.time()

    # Retrieving 2D image shape
    shp2 = [shp3[0], shp3[1]]

    # Managing voxel indices and pointers
    (idx, idx_ptr,
     numel, numel_ptr) = _mng_Idxs(idx, shp2)

    # Determinant Mask Criterion -- Threshold
    MdetThr = np.array(0.0, dtype=np.double)  # <<< Change Here for another TRESHOLD of the Determinant!!!
    MdetThr_ptr = MdetThr.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    # Normalising Mueller Matrix (by the element M(1,1) -- default)
    if not np.all(M[:, :, 0] == 1.0):
        (M, _) = norm_MM(M)

    # Getting pointer of Mueller Matrix
    M_ptr = _ptr_X(M.ravel(order='C'))

    # Initialising Output
    (Mdet, Mdet_ptr) = ini_Comp(shp2)
    (MdetMsk, MdetMsk_ptr) = ini_msk2(shp2)

    # Determining the Mueller Matrix Determinant
    # Calling the C-compiled function from the shared library

    mpMuelMatlibs.mp_comp_MM_det(Mdet_ptr, MdetMsk_ptr, M_ptr,
                                 MdetThr_ptr, idx_ptr, numel_ptr)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> compute_MM_det Performance: Elapsed time = {:.3f} s'.format(telaps))

    return Mdet, MdetMsk


def compute_I_satMsk(I, CamType=None):
    '''# Function to compute the saturation mask for the camera intensities I
	#
	# Call: I_satMsk = compute_I_satMsk(I,[CamType])
	#
	# *Inputs*
	# I: 3D stack of Intensity Components of shape shp3 = [dim[0],dim[1],16].
	#
	# [CamType]: optional string with the Camera Device Name used during the acquisition (see: default_CamType()).
	#
	# * Outputs *
	# I_satMsk: boolean validity mask of the Intensities saturation: shape [dim[0],dim[1]]'''

    if (CamType == None):
        CamType = default_CamType()

    # Defining the Gamma Dynamic Intensity Threshold for Saturation (Camera Property)
    I_thr_GammaDynamic = get_Cam_Params(CamType)[1]

    # Determining the Supra-Threshold Saturated Intensities (invalid pixels due to reflections)
    I_satMsk = np.all(I < I_thr_GammaDynamic, axis=-1)

    return I_satMsk


def compute_MM_eig_REls(M, idx=-1, VerboseFlag=0):
    '''# Function to compute the REAL Eigen*VALUES* ONLY of the Mueller Matrix
	#
	# Call: (REls,ElsMsk) = compute_MM_eig_REls( M , [idx] , [VerboseFlag] )
	#
	# *Inputs*
	# M: 3D stack of Mueller Matrix Components of shape shp3.
	# 	The matrix has the form [dim[0],dim[1],16].
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# * Outputs *
	# REls: unsorted diagonal REAL Eigen-Values of the Mueller Matrix decomposition: shape [dim[0],dim[1],4];
	# RElsMsk: logical mask of REAL Eigen-Values validity, based on physical criterion.
	#
	# NB: The Eigen-Decomposition has intrinsically COMPLEX values!
	#     This Function ONLY evaluates the REAL part of the Eigen-VALUES.
	#     For the Complete COMPLEX Eigen-Decomposition please use 'decomp_MM_eig_full'
	#
	# *** This is a python wrapper for the shared library: libmpMuelMat.so ***
	# *** The C-compiled shared library automatically enables and configures
	# *** multi-core processing for maximal performance using OpenMP libraries.'''

    shp3 = np.shape(M)
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "M" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "M" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    ## Initial Time (Total Performance)
    t = time.time()

    # Retrieving 2D image shape
    shp2 = [shp3[0], shp3[1]]

    # Managing voxel indices and pointers
    (idx, idx_ptr,
     numel, numel_ptr) = _mng_Idxs(idx, shp2)

    # Normalising Mueller Matrix (by the element M(1,1) -- default)
    if not np.all(M[:, :, 0] == 1.0):
        (M, _) = norm_MM(M)

    # Getting pointer of Mueller Matrix
    M_ptr = _ptr_X(M.ravel(order='C'))

    # Initialising Eigen-Values Output & Pointers (only REAL part)
    (REls, REls_ptr) = ini_REls(shp2)

    # Eigen-Vaules (Real) validity mask, based on physical criterion
    (ElsMsk, ElsMsk_ptr) = ini_msk2(shp2)

    # Mueller Matrix Eigen-Decomposition Multiplication-Factor
    nMag = np.array(0.25, dtype=np.double)  # <<< Change Value here if necessary
    nMag_ptr = nMag.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    # Physical Criterion -- Eigen-Values (Real) threshold
    ElsR_thr = np.array(-0.0001, dtype=np.double)  # <<< Change Threshold Value here for the Physical Criterion
    ElsR_thr_ptr = ElsR_thr.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    # Computing the Mueller Matrix Eigen-Decomposition
    # Calling the C-compiled function from the shared library

    mpMuelMatlibs.mp_comp_MM_eig_REls(REls_ptr, ElsMsk_ptr,
                                      M_ptr, nMag_ptr, ElsR_thr_ptr,
                                      idx_ptr, numel_ptr)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> decomp_MM_eig_REls Performance: Elapsed time = {:.3f} s'.format(telaps))

    return REls, ElsMsk


def sort_MM_REls(REls, ascendFlag=0):
    '''# Function to sort the (diagonal) REAL Eigen-Values Components of the Mueller Matrix Eigen-Decomposition
	# This function sorts the Real eigenvalues in a descending fashion (default)
	#
	# Call: srtREls = sort_MM_REls( REls , [ascendFlag] )
	#
	# *Inputs*
	# REls: 3D Stack of (diagonal) REAL Eigen-Values Components of shape shp3 = [dim[0],dim[1],4].
	#
	# [ascendFlag]: optional scalar boolean (0,1) as flag for ascending sorting.
	#				(default: 0)
	#
	# * Outputs *
	# srtREls: descending sorted Eigen-Values of the Mueller Matrix decomposition: shape [dim[0],dim[1],4];
	#          srtREls[:,:,0] = \lambda1
	#          srtREls[:,:,1] = \lambda2
	#          srtREls[:,:,2] = \lambda3
	#          srtREls[:,:,3] = \lambda4
	# 		   								with: \lambda1 >= \lambda2 >= \lambda3 >= \lambda4'''

    if ascendFlag:
        srtREls = np.sort(np.real(REls), axis=-1)
    else:
        srtREls = np.flip(np.sort(np.real(REls), axis=-1), axis=-1)

    return srtREls


def compute_MM_polar_LuChipman(M, idx=-1, VerboseFlag=0):
    '''# Function to compute the polar Lu-Chipman Decomposition of the Mueller Matrix
	#
	# Call: (MD,MR,Mdelta) = compute_MM_det( M , [idx] , [VerboseFlag] )
	#
	# *Inputs*
	# M: 3D stack of Mueller Matrix Components of shape shp3.
	# 	The matrix has the form [dim[0],dim[1],16].
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# * Outputs *
	# MD: Diattenuation Matrix of shape [dim[0],dim[1],16].
	# MR: Pahse Shift Matrix of shape [dim[0],dim[1],16].
	# Mdelta: Depolarisation Matrix of shape [dim[0],dim[1],16].
	#
	# *** This is a python wrapper for the shared library: libmpMuelMat.so ***
	# *** The C-compiled shared library automatically enables and configures
	# *** multi-core processing for maximal performance using OpenMP libraries.'''

    shp3 = np.shape(M)
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "M" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "M" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    ## Initial Time (Total Performance)
    t = time.time()

    # Retrieving 2D image shape
    shp2 = [shp3[0], shp3[1]]

    # Managing voxel indices and pointers
    (idx, idx_ptr,
     numel, numel_ptr) = _mng_Idxs(idx, shp2)

    # Normalising Mueller Matrix (by the element M(1,1) -- default)
    if not np.all(M[:, :, 0] == 1.0):
        (M, _) = norm_MM(M)

    # Getting pointer of Mueller Matrix
    M_ptr = _ptr_X(M.ravel(order='C'))

    # Initialising Output
    (MD, MD_ptr) = ini_MM(shp2)
    (MR, MR_ptr) = ini_MM(shp2)
    (Mdelta, Mdelta_ptr) = ini_MM(shp2)

    # Determining the Lu-Chipman Decomposition of the Mueller Matrix
    # Calling the C-compiled function from the shared library
    mpMuelMatlibs.mp_comp_MM_pol_LuChipman(MD_ptr, MR_ptr, Mdelta_ptr,
                                           M_ptr, idx_ptr, numel_ptr)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> compute_MM_polar_LuChipman Performance: Elapsed time = {:.3f} s'.format(telaps))

    return MD, MR, Mdelta


def compute_MM_polarim_Params(MD, MR, Mdelta, idx=-1, VerboseFlag=0):
    '''# Function to compute the polarimetric parameters from the Lu-Chipman Decomposition of the Mueller Matrix
	#
	# Call: polParams = compute_MM_polarim_Params( MD, MR, Mdelta , [idx] , [VerboseFlag] )
	#
	# *Inputs*
	# MD: Diattenuation Matrix of shape [dim[0],dim[1],16].
	#
	# MR: Pahse Shift Matrix of shape [dim[0],dim[1],16].
	#
	# Mdelta: Depolarisation Matrix of shape [dim[0],dim[1],16].
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#		 (default = -1) -- processing ALL pixels
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# * Outputs *
	# polParams: dictionary containing the following keys:
	#
	# 'totD': total Diattenuation of shape [dim[0],dim[1]].
	# 'linD': linear Diattenuation of shape [dim[0],dim[1]].
	# 'oriD': orientation of linear Diattenuation of shape [dim[0],dim[1]].
	# 'cirD': circular Diattenuation of shape [dim[0],dim[1]].
	#
	# 'totR': total Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'linR': linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'cirR': circular Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'oriR': orientation of linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'oriRfull': orientation of linear Phase Shift (Retardance) Full of shape [dim[0],dim[1]].
	#
	# 'totP': total Depolarisation of shape [dim[0],dim[1]].
	#
	# *** This is a python wrapper for the shared library: libmpMuelMat.so ***
	# *** The C-compiled shared library automatically enables and configures
	# *** multi-core processing for maximal performance using OpenMP libraries.'''

    shp3 = np.shape(MD)
    if (np.prod(np.shape(np.shape(MD))) != 3):
        raise Exception(
            'Input: "MD" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                np.shape(MD)))
    if (np.shape(MD)[-1] != 16):
        raise Exception(
            'Input: "MD" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                np.shape(MD)[-1]))
    if (np.prod(np.shape(np.shape(MR))) != 3):
        raise Exception(
            'Input: "MR" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                np.shape(MR)))
    if (np.shape(MR)[-1] != 16):
        raise Exception(
            'Input: "MR" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                np.shape(MR)[-1]))
    if (np.prod(np.shape(np.shape(Mdelta))) != 3):
        raise Exception(
            'Input: "Mdelta" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                np.shape(Mdelta)))
    if (np.shape(Mdelta)[-1] != 16):
        raise Exception(
            'Input: "Mdelta" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                np.shape(Mdelta)[-1]))
    if ((np.shape(MD) != np.shape(MR)) & (np.shape(MR) != np.shape(Mdelta))):
        raise Exception(
            'All inputs should have the *SAME* shape. The shape of the first argument is: {}'.format(np.shape(MD)))

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    ## Initial Time (Total Performance)
    t = time.time()

    # Retrieving 2D image shape
    shp2 = [shp3[0], shp3[1]]

    # Managing voxel indices and pointers
    (idx, idx_ptr,
     numel, numel_ptr) = _mng_Idxs(idx, shp2)

    # Getting pointer of Diattenuation Matrix MD
    MD_ptr = _ptr_X(MD.ravel(order='C'))

    # Getting pointer of Pahse Shift Matrix MR
    MR_ptr = _ptr_X(MR.ravel(order='C'))

    # Getting pointer of Depolarisation Matrix Mdelta
    Mdelta_ptr = _ptr_X(Mdelta.ravel(order='C'))

    ## Initialising Outputs
    # Diattenuation
    [totD, totD_ptr] = ini_Comp(shp2)
    [linD, linD_ptr] = ini_Comp(shp2)
    [oriD, oriD_ptr] = ini_Comp(shp2)
    [cirD, cirD_ptr] = ini_Comp(shp2)
    # Phase Shift (Retardance)
    [totR, totR_ptr] = ini_Comp(shp2)
    [linR, linR_ptr] = ini_Comp(shp2)
    [cirR, cirR_ptr] = ini_Comp(shp2)
    [oriR, oriR_ptr] = ini_Comp(shp2)
    [oriRfull, oriRfull_ptr] = ini_Comp(shp2)
    # Depolarisation
    [totP, totP_ptr] = ini_Comp(shp2)

    # Determining the Polarimetric Parameters from the Lu-Chipman Decomposition of the Mueller Matrix
    # Calling the C-compiled function from the shared library
    mpMuelMatlibs.mp_comp_MM_polarim_Params(totD_ptr, linD_ptr, oriD_ptr, cirD_ptr,
                                            totR_ptr, linR_ptr, cirR_ptr, oriR_ptr, oriRfull_ptr,
                                            totP_ptr,
                                            MD_ptr, MR_ptr, Mdelta_ptr,
                                            idx_ptr, numel_ptr)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' >> compute_MM_polarim_Params Performance: Elapsed time = {:.3f} s'.format(telaps))

    polParams = {'totD': totD,
                 'linD': linD,
                 'oriD': oriD,
                 'cirD': cirD,
                 'totR': totR,
                 'linR': linR,
                 'cirR': cirR,
                 'oriR': oriR,
                 'oriRfull': oriRfull,
                 'totP': totP}

    return polParams


def process_MM_pipeline(A, I, W, IN, idx=-1, CamType=None, VerboseFlag=0):
    '''# Function to run the end-to-end processing pipeline:
	# 1) Intensities and Calibrated Polarisation States are used to compute the Mueller Matrix
	# 2) Masks of valid pixels are retrieved from determinant, physical criterion and intensity saturation
	# 3) Polarimetric Matrices are computed with the Lu-Chipman decomposition of the Mueller Matrix
	# 4) Polarimetric Parameters are determined from the above matrices.
	#
	# Call: MMParams = process_MM_pipeline(A,I,W,IN,[idx],[CamType],[VerboseFlag])
	#
	# *Inputs*
	# A,I,W,IN:
	#           stacked 3D arrays with 16 components in the last dimension.
	# 		    All A, I, W  and IN must have the same shape: shp3 = A.shape,
	# 			corresponding to a 3D stack of 2D images in the form shp3 = [dim[0],dim[1],16].
	#
	# [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
	#	     if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
	#	     i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
	#		 (default = -1) -- processing ALL pixels
	#
	# [CamType]: optional string with the Camera Device Name used during the acquisition (see: default_CamType()).
	#
	# [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
	#                (default: 0)
	#
	# *Outputs*
	# MMParams: dictionary containing the following keys:
	#
	# 'nM': (normalised) Mueller Matrix
	# 'M11': normalising Mueller Matrix Component M(1,1)
	#
	# 'Mdetmsk': mask of the pixels with negative M determinant
	# 'Mphymsk': mask of the pixels satisfying the physical criterion
	# 'Isatmsk': mask of the pixels with saturated intensities (e.g. reflections)
	# 'Msk': final mask of the valid pixels obtained as logical AND of the above ones
	#
	# 'Els': Real part of the Mueller Matrix EigenValues (unsorted)
	#
	# 'MD': polarimetric matrix of diattenuation
	# 'MR': polarimetric matrix of phase shift (retardance)
	# 'Mdelta': polarimetric matrix of depolarisation
	#
	# 'totD': total Diattenuation of shape [dim[0],dim[1]].
	# 'linD': linear Diattenuation of shape [dim[0],dim[1]].
	# 'oriD': orientation of linear Diattenuation of shape [dim[0],dim[1]].
	# 'cirD': circular Diattenuation of shape [dim[0],dim[1]].
	#
	# 'totR': total Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'linR': linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'cirR': circular Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'oriR': orientation of linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	# 'oriRfull': orientation of linear Phase Shift (Retardance) Full of shape [dim[0],dim[1]].
	#
	# 'totP': total Depolarisation of shape [dim[0],dim[1]].
	'''

    if (np.prod(np.shape(A.shape)) != 3):
        raise Exception(
            'Input: "A" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                A.shape))
    if (A.shape[-1] != 16):
        raise Exception(
            'Input: "A" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                A.shape[-1]))
    if (np.prod(np.shape(I.shape)) != 3):
        raise Exception(
            'Input: "I" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                I.shape))
    if (I.shape[-1] != 16):
        raise Exception(
            'Input: "I" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                I.shape[-1]))
    if (np.prod(np.shape(W.shape)) != 3):
        raise Exception(
            'Input: "W" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                W.shape))
    if (W.shape[-1] != 16):
        raise Exception(
            'Input: "W" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                W.shape[-1]))
    if (np.prod(np.shape(IN.shape)) != 3):
        raise Exception(
            'Input: "IN" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                IN.shape))
    if (IN.shape[-1] != 16):
        raise Exception(
            'Input: "IN" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                IN.shape[-1]))
    if not ((A.shape == I.shape) & (I.shape == W.shape) & (W.shape == IN.shape)):
        raise Exception('Inputs MUST All have the same shape!')

    if (CamType == None):
        CamType = default_CamType()

    shp3 = np.shape(A)

    ## Initial Time (Total Performance)
    t = time.time()

    M, nM = compute_MM_AIW(A, I, W, idx, VerboseFlag)

    M11 = M[:, :, 0].squeeze()

    Mdetmsk = compute_MM_det(nM, idx, VerboseFlag)[1]

    Els, Elsmsk = compute_MM_eig_REls(nM, idx, VerboseFlag)

    Isatmsk = compute_I_satMsk(IN, CamType)

    Msk = Mdetmsk & Elsmsk & Isatmsk

    MD, MR, Mdelta = compute_MM_polar_LuChipman(nM, idx, VerboseFlag)

    polParams = compute_MM_polarim_Params(MD, MR, Mdelta, idx, VerboseFlag)

    ## Final Time (Total Performance)
    telaps = time.time() - t
    if VerboseFlag:
        print(' ')
        print(' ')
        print(
            ' >> process_MM_pipeline Performance [{:d},{:d}]: Elapsed time = {:.3f} s'.format(shp3[0], shp3[1], telaps))

    MMParams = {'nM': nM,
                'M11': M11,
                'Mdetmsk': Mdetmsk,
                'Mphymsk': Elsmsk,
                'Isatmsk': Isatmsk,
                'Msk': Msk,
                'Els': Els,
                'MD': MD,
                'MR': MR,
                'Mdelta': Mdelta}

    MMParams.update(polParams)

    return MMParams


def validate_libmpMuelMat_testDataMAT():
    '''# Function to automatically run the algorithmic validation over a reference pre-computed dataset.
	# This function loads polarimetric data from a pre-computed and exported MATLAB dataset,
	# then, the re-computes the same variables with the implemented algorithmics in libmpMuelMat library.
	# Eventually the results are compared pixel-wise for all variables in the dataset and
	# statistics on computational errors are provided and displayed.
	#
	# Please set the correct path to the MAT datafile prior to running this validation.
	'''

    # Raw Input Data
    A, I, W, IN = get_testDataMAT()

    # Reference Processed Data (MATLAB)
    refMAT = _get_validDataMAT()

    # Processed Data with libmpMuelMat (Python + C)
    MMParams = process_MM_pipeline(A, I, W, IN, -1, default_CamType(), 1)  # All pixels, Verbose = true

    ## Mueller Matrix Errors
    # Normalised Mueller Matrix Error
    nM_err = np.abs(MMParams['nM'] - refMAT['nM'])

    # M11 Error
    M11_err = np.abs(MMParams['M11'] - refMAT['M11'])

    ## Masks Errors (DSC Score)
    # Mdetmsk DSC
    MdetDSC = _compute_masks_DSC(MMParams['Mdetmsk'], refMAT['Mdetmsk'])

    # Mphymsk DSC
    MphyDSC = _compute_masks_DSC(MMParams['Mphymsk'], refMAT['Mphymsk'])

    # Isatmsk DSC
    IsatDSC = _compute_masks_DSC(MMParams['Isatmsk'], refMAT['Isatmsk'])

    # Mask Final DSC
    MskDSC = _compute_masks_DSC(MMParams['Msk'], refMAT['Msk'])

    ## EigenValues Errors
    # Sorted EigenValues
    Els_err = np.abs(sort_MM_REls(MMParams['Els']) - sort_MM_REls(refMAT['Els']))

    # EigenValue \lambda1 Mask DSC
    El1DSC = _compute_masks_DSC(sort_MM_REls(MMParams['Els'])[:, :, 0].squeeze() > 0,
                                sort_MM_REls(refMAT['Els'])[:, :, 0].squeeze() > 0)

    # Eigenvalue \lambda2 Mask DSC
    El2DSC = _compute_masks_DSC(sort_MM_REls(MMParams['Els'])[:, :, 1].squeeze() > 0,
                                sort_MM_REls(refMAT['Els'])[:, :, 1].squeeze() > 0)

    # Eigenvalue \lambda3 Mask DSC
    El3DSC = _compute_masks_DSC(sort_MM_REls(MMParams['Els'])[:, :, 2].squeeze() > 0,
                                sort_MM_REls(refMAT['Els'])[:, :, 2].squeeze() > 0)

    # EigenValue \lambda4 Mask DSC
    El4DSC = _compute_masks_DSC(sort_MM_REls(MMParams['Els'])[:, :, 3].squeeze() > 0,
                                sort_MM_REls(refMAT['Els'])[:, :, 3].squeeze() > 0)

    ## Lu-Chipman Polar Decomposition Errors
    # MD (Diattenuation) Error
    MD_err = np.abs(MMParams['MD'] - refMAT['MD'])

    # MR (Phase Shift, aka Retardance) Error
    MR_err = np.abs(MMParams['MR'] - refMAT['MR'])

    # Mdelta (Depolarisation) Error
    Mdelta_err = np.abs(MMParams['Mdelta'] - refMAT['Mdelta'])

    ## Polarimetric Parameters Errors
    # Total Diattentuation
    totD_err = np.abs(MMParams['totD'] - refMAT['totD'])

    # Linear Diattenuation
    linD_err = np.abs(MMParams['linD'] - refMAT['linD'])

    # Circular Diattenuation
    cirD_err = np.abs(MMParams['cirD'] - refMAT['cirD'])

    # Orientation of Linear Diattenuation
    oriD_err = np.abs(MMParams['oriD'] - refMAT['oriD'])

    # Total Retardance
    totR_err = np.abs(MMParams['totR'] - refMAT['totR'])

    # Linear Retardance
    linR_err = np.abs(MMParams['linR'] - refMAT['linR'])

    # Circular Retardance
    cirR_err = np.abs(MMParams['cirR'] - refMAT['cirR'])

    # Orientation of Linear Retardance
    oriR_err = np.abs(MMParams['oriR'] - refMAT['oriR'])

    # Orientation of Linear Retardance Full
    oriRfull_err = np.abs(MMParams['oriRfull'] - refMAT['oriRfull'])

    # Total Depolarisation
    totP_err = np.abs(MMParams['totP'] - refMAT['totP'])

    ## Printing Validation/Testing Results by comparing the Reference Data to the Processed Data using libmpMuelMat

    print(' ')
    print('-------------------------------------------------------------------------')
    print('    * Validation of libmpMuelMat on reference testing Data (MATLAB) *    ')
    print(' ')
    print(' >> Errors reported as:   min, max, avg, std   of  err = abs( X - Xref ) ')
    print(' ')
    print(' >> Masks overlap reported as : DSC score [0,1]')
    print('-------------------------------------------------------------------------')
    print(' ')
    print(' DATA\tmin(err)\tmax(err)\tavg(err)\tstd(err)\n')
    print(' nM\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(nM_err), np.max(nM_err), np.mean(nM_err), np.std(nM_err)))
    print(' M11\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(M11_err), np.max(M11_err), np.mean(M11_err), np.std(M11_err)))
    print(' Els\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(Els_err), np.max(Els_err), np.mean(Els_err), np.std(Els_err)))
    print(' MD\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(MD_err), np.max(MD_err), np.mean(MD_err), np.std(MD_err)))
    print(' MR\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(MR_err), np.max(MR_err), np.mean(MR_err), np.std(MR_err)))
    print(' Mdlt\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(Mdelta_err), np.max(Mdelta_err), np.mean(Mdelta_err),
                                                   np.std(Mdelta_err)))
    print(' totD\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(totD_err), np.max(totD_err), np.mean(totD_err),
                                                   np.std(totD_err)))
    print(' linD\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(linD_err), np.max(linD_err), np.mean(linD_err),
                                                   np.std(linD_err)))
    print(' cirD\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(cirD_err), np.max(cirD_err), np.mean(cirD_err),
                                                   np.std(cirD_err)))
    print(' oriD\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(oriD_err), np.max(oriD_err), np.mean(oriD_err),
                                                   np.std(oriD_err)))
    print(' totR\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(totR_err), np.max(totR_err), np.mean(totR_err),
                                                   np.std(totR_err)))
    print(' linR\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(linR_err), np.max(linR_err), np.mean(linR_err),
                                                   np.std(linR_err)))
    print(' cirR\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(cirR_err), np.max(cirR_err), np.mean(cirR_err),
                                                   np.std(cirR_err)))
    print(' oriR\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(oriR_err), np.max(oriR_err), np.mean(oriR_err),
                                                   np.std(oriR_err)))
    print(' oriRf\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(oriRfull_err), np.max(oriRfull_err), np.mean(oriRfull_err),
                                                    np.std(oriRfull_err)))
    print(' totP\t{:e}\t{:e}\t{:e}\t{:e}\n'.format(np.min(totP_err), np.max(totP_err), np.mean(totP_err),
                                                   np.std(totP_err)))
    print('-------------------------------------------------------------------------')
    print(' ')
    print(' MASK\tDSC\n')
    print(' Mdet\t{:.3f}\n'.format(MdetDSC))
    print(' Mphy\t{:.3f}\n'.format(MphyDSC))
    print(' Isat\t{:.3f}\n'.format(IsatDSC))
    print(' Final\t{:.3f}\n'.format(MskDSC))
    print(' MEl1\t{:.3f}\n'.format(El1DSC))
    print(' MEl2\t{:.3f}\n'.format(El2DSC))
    print(' MEl3\t{:.3f}\n'.format(El3DSC))
    print(' MEl4\t{:.3f}\n'.format(El4DSC))
    print('-------------------------------------------------------------------------')


def _compute_masks_DSC(msk, msk_ref):
    '''# Function to compute the Dice Score (DSC) - overlap - between two binary masks.
	# The Dice Score is defined as:
	# DSC = ( 2 * sum(msk AND msk_ref) ) / ( sum(msk) + sum(msk_ref) )
	#
	# Call: DSC = _compute_masks_DSC(msk,msk_ref)
	#
	# *Inputs*
	# msk: binary array of arbitrary shape
	#
	# msk_ref: binary array (Reference) of same shape as msk
	#
	# *Outputs*
	# DSC: real scalar [0,1] indicating the matching overlap between the input masks: 1 for perfect match
	#
	'''
    # Function to compute the Dice Score (DSC) - overlap - between two binary masks (msk and msk_ref)
    DSC = (2 * np.sum(msk & msk_ref)) / (np.sum(msk) + np.sum(msk_ref))
    return DSC


def test_OpenMP():
    '''# Function to test the correct C source-code compilation linking to multi-processing libraries (openMP)'''

    # Loading Shared Library
    mpMuelMatlibs = _loadClib()

    print(' ')

    mpMuelMatlibs.test_openMP()

    print(' ')
    print(' Please, run this testing function few more times and check the order of the resulting sequence...')
    print(
        ' If the ORDER CHANGES every time and it is NOT SEQUENTIAL, the parallel-computing (openMP) libraries are correctly linked!')


def test_process_MM_pipeline(): # TO BE MODIFIED!!!
    '''# Function to Test the end-to-end Mueller Matrix processing pipeline for the provided testing raw data.
	# This testing data is evaluated for wavelength = 550nm.
	# NB: it is required to have run the test calibration first!
	#     In absence of test calibration, the latter will be run first.
	#
	# Call: MMParams = test_process_MM_pipeline()
	#'''

    wlen = 550
    wlen_str = "{:d}".format(wlen)
    CamType = default_CamType(-1)

    shp2 = get_Cam_Params(CamType)[0]

    # Generate Synthetic State/Acquisition Matrices (this can be replaced by a system calibration step)
    (A, W) = gen_AW(shp2, wlen)

    # After loading A,W, or after performing the test calibration
    if not ((A == None).any() | (W == None).any()):  # If successful

        # Checking for input raw Intensities and Loading them
        test_scan_path = _get_test_scan_path()
        I_cod_Filename = test_scan_path + wlen_str + '_Intensite.cod'
        N_cod_Filename = test_scan_path + wlen_str + '_Bruit.cod'

        if (_chkFilePath(I_cod_Filename) & _chkFilePath(N_cod_Filename)):
            print(' ')
            print(' >> Loading Intensity and Background Noise Matrices from Test Scan: ...')

            IN = read_cod_data_X3D(I_cod_Filename, CamType, isRawFlag)
            NO = read_cod_data_X3D(N_cod_Filename, CamType, isRawFlag)
            I = IN - NO
            print('    Done')

            # Processing
            MMParams = process_MM_pipeline(A, I, W, IN, -1, CamType, 1)  # All pixels, Verbose = true

            print(' ')
            print(' -------------------------------------------------------------')
            print(' >> Polarimetric Parameters are stored in the output dictionay.')
            print(' >> Access data in the output dictionary as listed in')
            print('        help(libmpMuelMat.process_MM_pipeline)')
            print(' ')
            print(' >> Visualise data using built-in plots')
            print('        help(libmpMuelMat.show_Montage)')
            print('        help(libmpMuelMat.show_Comp)')
            print('        help(libmpMuelMat.show_REls)')
            print(' ')

        else:
            print(' ')
            print(' <!> Intensity and Background Noise Matrices corrupted or NOT FOUND in', test_scan_path, '-- Abort!')
            MMParams = None

    else:  # If A,W Loading Failed or Test Calibration Failed
        print(' ')
        print(' <!> Loading of A,W or Test Calibration: FAILED! -- Test Processing Pipeline -- Abort!')
        MMParams = None

    return MMParams


def show_Montage(X3D):
    '''# Function to display the 16 components (e.g. of Mueller Matrix) in a montage form (4x4)
	# This function is based on matplotlib.
	#
	# Call: show_Montage( X3D )
	#
	# *Inputs*
	# X3D: 3D stack of 2D Components of shape shp3.
	# 	   The matrix X must have shape equal to [dim[0],dim[1],16].'''

    shp3 = np.shape(X3D)
    if (np.prod(np.shape(shp3)) != 3):
        raise Exception(
            'Input: "X3D" should have shape of a 3D image, e.g. (idx0, idx1, idx2). The shape value was found: {}'.format(
                shp3))
    if (shp3[-1] != 16):
        raise Exception(
            'Input: "X3D" should have shape 16 components in the last dimension. The number of elements in the last dimension is: {}'.format(
                shp3[-1]))

    X_montage = np.concatenate((np.concatenate(
        (X3D[:, :, 0].squeeze(), X3D[:, :, 1].squeeze(), X3D[:, :, 2].squeeze(), X3D[:, :, 3].squeeze()), axis=1),
                                np.concatenate((X3D[:, :, 4].squeeze(), X3D[:, :, 5].squeeze(), X3D[:, :, 6].squeeze(),
                                                X3D[:, :, 7].squeeze()), axis=1),
                                np.concatenate((X3D[:, :, 8].squeeze(), X3D[:, :, 9].squeeze(), X3D[:, :, 10].squeeze(),
                                                X3D[:, :, 11].squeeze()), axis=1),
                                np.concatenate((X3D[:, :, 12].squeeze(), X3D[:, :, 13].squeeze(),
                                                X3D[:, :, 14].squeeze(), X3D[:, :, 15].squeeze()), axis=1)), axis=0)
    plt.imshow(X_montage)
    plt.colorbar(shrink=0.8)
    plt.xticks([])
    plt.yticks([])
    plt.show()


def show_REls(REls):
    '''# Function to display the 4 Real EigenValues components of Mueller Matrix Eigen-Decomposition in a montage form (1x4)
	# This function is based on matplotlib.
	#
	# Call: show_REls( REls )
	#
	# *Inputs*
	# REls: 3D stack of 2D EigenValues Components of shape shp3 = [dim[0],dim[1],4].
	#
	# NB: The displayed Real EigenValues are sorted in a descending fashion: \lambda1 >= \lambda2 >= \lambda3 >= \lambda4'''

    REls = sort_MM_REls(REls)

    REls_montage = np.concatenate((REls[:, :, 0].squeeze(),
                                   REls[:, :, 1].squeeze(),
                                   REls[:, :, 2].squeeze(),
                                   REls[:, :, 3].squeeze()), axis=1)

    plt.imshow(REls_montage)
    plt.colorbar(orientation="horizontal", shrink=0.8)
    plt.xticks([])
    plt.yticks([])
    plt.show()


def show_Comp(X2D):
    '''# Function to display an individual 2D component (e.g. one component of the Mueller Matrix coeffs, or a Mask)
	# This function is based on matplotlib.
	#
	# Call: show_Comp( X2D )
	#
	# *Inputs*
	# X2D: 2D Image of shape shp2 = [dim[0],dim[1]].'''

    if (np.prod(np.shape(np.shape(X2D))) != 2):
        raise Exception(
            'Input: "X2D" should have shape of a 2D image, e.g. (idx0, idx1). The shape value was found: {}'.format(
                np.shape(X2D)))

    plt.imshow(X2D)
    plt.colorbar(shrink=0.8)
    plt.xticks([])
    plt.yticks([])
    plt.show()
