------------------------------------------------------------------------------
* libmpMuelMat: Open Library for Polarimetric Mueller Matrix Image Processing
* version: 1.0 

* project: HORAO - Inselspital, Bern, CH -- 2022
* developer: Dr. Stefano Moriconi (stefano.nicola.moriconi@gmail.com)
-----------------------------------------------------------------------------

**************************************
 libmpMuelMat -- ReadMe Documentation 
**************************************

a. Introduction
b. System Requirements
c. Package Contents
d. Installation and Configuration
e. Functions and Help
f. Tests and Examples


a. Introduction

	The libmpMuelMat library is a multi-platform set of computational tools for polarimetric Mueller matrix image processing.

	The library builds on an integration of compiled C codebase and Python for an optimised and streamlined user experience.
	The libmpMuelMat library embeds high-performance computational algorithms, ported from state-of-the-art methods [1-4],
	and provides and optimised and stable interface for machine-learning designs, as well as, nearly real-time applications for 
	translational and experimental set-ups.
	
	The library is open-source and free of use. See GitHub License. 


	[1] Compain, E., Poirier, S., & Drevillon, B. (1999). General and self-consistent method for the calibration of polarization modulators, polarimeters, and Mueller-matrix ellipsometers. Applied optics, 38(16), 3490-3502.
	[2] Lu, S. Y., & Chipman, R. A. (1996). Interpretation of Mueller matrices based on polar decomposition. JOSA A, 13(5), 1106-1113.
	[3] Ossikovski, R., De Martino, A., & Guyot, S. (2007). Forward and reverse product decompositions of depolarizing Mueller matrices. Optics letters, 32(6), 689-691.
	[4] Ossikovski, R., Anastasiadou, M., & De Martino, A. (2008). Product decompositions of depolarizing Mueller matrices with negative determinants. Optics communications, 281(9), 2406-2410.

b. System Requirements

	The libmpMuelMat library is C- and Python-based as well as multi-platform (Linux, Mac, Windows)
	
	Python 3.5+ -- https://www.python.org/downloads/ 
		numpy (1.21.5), 
		ctypes (1.1.0),
		matplotlib (3.5.1),
		scipy (1.7.3)

    C/C++ Compiler + Parallel and Multi-Processing libraries: 
    	
    	* Linux - Ubuntu 20.04.2 LTS
    	- GCC 9.4 or later (default) -- https://gcc.gnu.org/ 
    	- OpenMP (included in GCC) -- https://www.openmp.org/ 

    	* Mac - MacOS Catalina 10.15.7
    	- Homebrew 3.5.7   [ from terminal: /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"]
    	- GCC 9.4 or later [ from terminal: brew install gcc ]
    	- OpenMP (included in GCC) -- https://www.openmp.org/

    	* Windows - Win10 or later
    	- MSYS2 -- https://www.msys2.org/ 
    	- GCC 9.4 or later -- install from MSYS2 (see below)
    	- OpenMP (included in GCC) -- https://www.openmp.org/

	*** WINDOWS ***
	1) Download MSYS2:
	https://github.com/msys2/msys2-installer/releases/download/2022-09-04/msys2-x86_64-20220904.exe

	2) Follow the instructions to install MSYS2 on:
	https://www.msys2.org/   -- click NEXT until complete
	
	3) Launch the MINWG64 environment:
	Start Menu >> Programs >> MSYS2 >> MSYS2 MINGW64
	
	4) Install GCC from the MINGW64 environment [terminal]:
	$ pacman -S mingw-w64-x86_64-gcc
	
	5) Verify GCC has been succesfully installed:
	$ gcc --version
	
		it should display '12.2.0' or later
		

c. Package Contents

	libmpMuelMat.py -- python library with polarimetric Mueller matrix image processing tools
	/C-libs         -- folder with C source code to be compiled in the target shared library: /C-libs/libmpMuelMat.so
	ReadMe.txt		-- this file
	/TestData	    -- folder cointaining testing data for examples either processed in matlab (.mat) or raw (.cod)


d. Installation and Configuration

	[Installation]

	* Compiling the C source code into the shared library 'libmpMuelMat.so'

		open (with a text editor) and check first instructions (commented lines) in ./C-libs/compileMeFirst.sh

		[LINUX, MAC] after possible adjustments run in the terminal:

		$ cd ./C-libs
		$ bash compileMeFirst.sh

		[WINDOWS] after editing the *adjustments* (e.g. using notepad) launch the MINGW64 environment and run in the terminal:

		$ cd ./C-libs
		$ bash compileMeFirst.sh 
		
        
        [WINDOWS] once succesfully compiled, *add* the MINGW64 shared library folder to the PATHS of the System:

        Start >> Edit the System Environmental Variables >> Environment Variables... >> System Variables >> Path >> New: MSYS2_MINGW64_SHARED_LIBS_PATH

        with MSYS2_MINGW64_SHARED_LIBS_PATH = 'C:\msys64\mingw64\bin'  (by default)
 

	[Configuration]

	[WINDOWS ONLY]: edit (notepad) the python library 'libmpMuelMat.py' lines: (80,81) to correctly reference the compiled shared library (.dll)
	

	* Loading the library in python (after launching e.g. ipython):

		>> import libmpMuelMat

	* Displaying the library dipendencies:

		>> libmpMuelMat.list_Dependencies()
		
		-- Please adjust the paths and dependencies to make it consistent, prior to using the tools.

	* Testing C-compiled source code correctly linking to multi-processing libraries (OpenMP)

		>> libmpMuelMat.test_OpenMP()

		-- If the parallel-computinf and multi-processing libraries are not correctly linked,
		   the library will not be optimised for performance.

	* Displaying library credits:

		>> libmpMuelMat.credits()

	* (Unit)Testing and Validating library:

		>> libmpMuelMat.validate_libmpMuelMat_testData()


e. Functions and Help

	The list of available functions and associated help is available by typing:

		help(libmpMuelMat)

	NAME
    libmpMuelMat

	FUNCTIONS
    
    compute_I_satMsk(I, CamType=None)
        # Function to compute the saturation mask for the camera intensities I
        #
        # Call: I_satMsk = compute_I_satMsk(I,[CamType])
        #
        # *Inputs*
        # I: 3D stack of Intensity Components of shape shp3 = [dim[0],dim[1],16].
        #
        # [CamType]: optional string with the Camera Device Name used during the acquisition (see: default_CamType()).
        #
        # * Outputs *
        # I_satMsk: boolean validity mask of the Intensities saturation: shape [dim[0],dim[1]]
    
    compute_MM_AIW(A, I, W, idx=-1, VerboseFlag=0)
        # Function to compute the Mueller Matrix from the equation M = AIW
        #
        # Call: (M,nM) = compute_MM_AIW_new( A , I , W , [idx] , [VerboseFlag] )
        #
        # *Inputs*
        # A, I, W:
        #       stacked 3D arrays with 16 components in the last dimension.
        #       All A, I, amd W must have the same shape: shp3 = A.shape,
        #       corresponding to a 3D stack of 2D images in the form shp3 = [dim[0],dim[1],16].
        #
        #   >> NB: all A,I,W should have a c-like ordering (not fortran-like ordering) for best performance!
        #
        # [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
        #            if idx is a scalar equal to -1, *ALL* indices are considered (default),
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
        #
        # [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
        #                (default: 0)
        #
        # * Outputs *
        # M: 3D stack of Mueller Matrix Components of shape shp3.
        #       The matrix has the form [dim[0],dim[1],16].
        #
        # nM: 3D stack of normalised Mueller Matrix Components of shape shp3 = [dim[0],dim[1],16].
        #         Each Component is normalised by M(1,1) as default.
        #
        # *** This is a python wrapper for the shared library: libmpMuelMat.so ***
        # *** The C-compiled shared library automatically enables and configures
        # *** multi-core processing for maximal performance using OpenMP libraries.

    compute_MM_det(M, idx=-1, VerboseFlag=0)
        # Function to compute the determinant of the Mueller Matrix
        #
        # Call: (Mdet,MdetMsk) = compute_MM_det( M , [idx] , [VerboseFlag] )
        #
        # *Inputs*
        # M: 3D stack of Mueller Matrix Components of shape shp3.
        #       The matrix has the form [dim[0],dim[1],16].
        #
        # [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
        #            if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
        #
        # [VerboseFlag]: optional scalar boolean (0,1) as flag for displaying performance (computational time)
        #                (default: 0)
        #
        # * Outputs *
        # Mdet: final Mueller Matrix determinant image of shape [dim[0],dim[1]],
        # MdetMsk: boolean Mask of validity for the Determinant of the Mueller Matrix
        #                  MdetMsk = Mdet > 0   (default)
        #
        # *** This is a python wrapper for the shared library: libmpMuelMat.so ***
        # *** The C-compiled shared library automatically enables and configures
        # *** multi-core processing for maximal performance using OpenMP libraries.
    
    compute_MM_eig_REls(M, idx=-1, VerboseFlag=0)
        # Function to compute the REAL Eigen*VALUES* ONLY of the Mueller Matrix
        #
        # Call: (REls,ElsMsk) = compute_MM_eig_REls( M , [idx] , [VerboseFlag] )
        #
        # *Inputs*
        # M: 3D stack of Mueller Matrix Components of shape shp3.
        #       The matrix has the form [dim[0],dim[1],16].
        #
        # [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
        #            if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
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
        # *** multi-core processing for maximal performance using OpenMP libraries.
    
    compute_MM_polar_LuChipman(M, idx=-1, VerboseFlag=0)
        # Function to compute the polar Lu-Chipman Decomposition of the Mueller Matrix
        #
        # Call: (MD,MR,Mdelta) = compute_MM_det( M , [idx] , [VerboseFlag] )
        #
        # *Inputs*
        # M: 3D stack of Mueller Matrix Components of shape shp3.
        #       The matrix has the form [dim[0],dim[1],16].
        #
        # [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
        #            if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
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
        # *** multi-core processing for maximal performance using OpenMP libraries.
    
    compute_MM_polarim_Params(MD, MR, Mdelta, idx=-1, VerboseFlag=0)
        # Function to compute the polarimetric parameters from the Lu-Chipman Decomposition of the Mueller Matrix
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
        #            if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
        #                (default = -1) -- processing ALL pixels
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
        # *** multi-core processing for maximal performance using OpenMP libraries.
    
    credits()
        # Function to display the credits of libmpMuelMat library.

	default_CamType(CamID=None)
        # Define the Default Camera Type used in the Polarimetric Acquisitions
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
        # CamID         CamType
        # 0     ->      'Stingray IPM2' (default)
        # 1     ->      'Prosilica'
        # 2     ->      'JAI'
        # 3     ->      'JAI Packing 2x2'
        # 4     ->      'JAI Binning'
        # 5     ->      'Stingray'
        # 6     ->      'Stingray IPM1'
        #
        # -1    ->  'TEST' -- used for (Unit)Testing
    
    gen_AW(shp2=None, wlen=550)
        #Function to generate synthetic polarisation state/acquisition matrices A,W of arbitrary shape.
        # The polarisation matrices A,W can be used to compute the Mueller Matrix decomposition,
        # given an input set of intensities I.
        #
        # Call: (A,W) = gen_AW([shp2],[wlen])
        #
        # *Inputs*
        # shp2: shape of the 2D A, I, and W images as (dim0, dim1)
        #               NB: is shp2 is not provided, a default shape is retrieved, based on default camera type.
        #
        # wlen: integer scalar for the polarimetric wavelength in nm [default: 550]
        #               supported wavelengths: [550, 650]
        #
        # *Outputs*
        #
        # A,W: 3D arrays of shape [shp2[0],shp2[1],16] with values from previous calibrations.
        #      NB: the values are statistical estimations, and should be used in synthetic set-up only,
        #          in order to simulate an artificial calibration of the system.
        #
        # NB: only 2 wavelength are currently supported: 550nm (default) and 650nm
        #     other input wavelengths will produce randomly distributed (Gaussian) matrices as output.
    
    get_Cam_Params(CamType)
        # Function to retrieve the polarimetric Camera Parameters
        # Several camera types are listed below
        #
        # Call: (ImgShape2D,GammaDynamic) = get_Cam_Params(CamType)
        #
        # *Inputs*
        # CamType: string identifying the camera type (see: default_CamType()).
        #
        # * Outputs *
        # ImgShape2D: list containing the camera pixel-wise size as [dim[0],dim[1]]
        # GammaDynamic: scalar intensity as maximum value for detecting saturation/reflection
    
    get_testDataMAT()
        # Function to retrieve variables from the MATLAB test Data
        # The loaded variables are:
        # A,W: polarisation states matrices obtained from calibration to compute the Mueller Matrix
        # I: intensities (background noise is subtracted) to compute the Mueller Matrix
        # IN: raw intensities
        #
        # NB: as the variables are natively from a MATLAB environment (fortran ordering),
        #     the data is re-ordered in a C-like fashion in line with subsequent processing.
        #
        # Variables are returned in the following order: A,I,W,IN

    ini_Comp(shp2)
        # Function to initialise a 2D Component (can be used in C compiled code with pointer)
        # This function set the data type to double (i.e. np.double).
        #
        # Call: (X2D,X2D_ptr) = ini_Comp( shp2 )
        #
        # *Inputs*
        # shp2: shape of the 2D image Component as (dim0, dim1)
        #
        # *Outputs*
        # X2D: 2D Image Component of shape (shp2[0],shp2[1]) initialised as zeros
    
    ini_MM(shp2)
        # Function to initialise the Mueller Matrix Components used in the compiled Shared Library
        # This function set the data type to double (i.e. np.double).
        #
        # Call: (M,M_ptr) = ini_MM( shp2 )
        #
        # *Inputs*
        # shp2: shape of the 2D Mueller Matrix image as (dim0, dim1)
        #
        # *Outputs*
        # M: Mueller Matrix of shape (shp2[0],shp2[1],16) initialised as zeros
        # M_ptr: C-like pointer to the Matrix
    
    ini_REls(shp2)
        # Function to initialise the REAL EigenVALUES of the Mueller Matrix for the compiled Shared Library
        # This function set the data type to double (i.e. np.double).
        #
        # Call: (REls,REls_ptr) = ini_REls( shp2 )
        #
        # *Inputs*
        # shp2: shape of the 2D Mueller Matrix REAL EigenValue Component as (dim0, dim1)
        #
        # *Outputs*
        # REls: REAL EigenVALUES of the Mueller Matrix of shape (shp2[0],shp2[1],4) initialised as zeros
        # REls_ptr: C-like pointer to the variable
    
    ini_msk2(shp2)
        # Function to initialise the logical mask variable (can be used in the compiled Shared Library with the pointer)
        # This function set the data type to boolean, and returns the associated pointer.
        #
        # Call: (msk2,msk2_ptr) = ini_msk2( shp2 )
        #
        # *Inputs*
        # shp2: shape of the 2D image as (dim0, dim1)
        #
        # *Outputs*
        # msk2: logical validity mask of 2D shape (shp2), initialised as 'True'
        # msk2_ptr: pointer of the logical validity mask.
    
    list_Dependencies()
        # Function to List all current dependencies of the libmpMuelMat library
        #
        # Please update any incorrect dependency prior to using the library.

	map_msk2_to_idx(msk2)
        # Function to determine the C-like linear indices, given a logical mask of a 2D image.
        #
        # Call: idx = map_msk2_to_idx( msk2 )
        #
        # *Inputs*
        # msk2: boolean mask of a 2D image of shape (dim0, dim1)
        #
        # *Outputs*
        # idx: C-like linear indices corresponding to the 'True' voxels in msk2
        #       e.g. if msk3 has shape (3,3) and the only true value is in the middle,
        #       i.e. msk2[1,1] = True, the idx array will be a scalar equal to 4.
        #   NB: indexing starts from 0
    
    norm_MM(M)
        # Function to normalise the Mueller Matrix coefficients by the first one (M11)
        #
        # Call: (nM,M11) = norm_MM( M )
        #
        # *Inputs*
        # M: 3D stack of Mueller Matrix Components of shape shp3.
        #       The matrix has the form [dim[0],dim[1],16].
        #
        # * Outputs *
        # nM:  normalised 3D stack of Mueller Matrix Components of shape shp3.
        # M11: 2D normalising coefficient (shape: [dim[0],dim[1]] )of the Mueller Matrix

    process_MM_pipeline(A, I, W, IN, idx=-1, CamType=None, VerboseFlag=0)
        # Function to run the end-to-end processing pipeline:
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
        #                   All A, I, W  and IN must have the same shape: shp3 = A.shape,
        #                       corresponding to a 3D stack of 2D images in the form shp3 = [dim[0],dim[1],16].
        #
        # [idx]: optional 1-D array of C-like linear indices obtained from the function 'map_msk2_to_idx'
        #            if idx is a scalar equal to -1, *ALL* indices (pixels) are considered,
        #            i.e. idx = np.array(np.arange(0,numel)), with numel = np.prod([dim[0],dim[1]])
        #                (default = -1) -- processing ALL pixels
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
    
    read_cod_data_X2D(input_cod_Filename, CamType=None, VerboseFlag=0)
        # Function to read (load) 2D data from exported dataset in '.cod' binary format.
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
        #          NB: the dimensions dim[0] and dim[1] are given by the camera parameters.

    read_cod_data_X3D(input_cod_Filename, CamType=None, isRawFlag=0, VerboseFlag=0)
        # Function to read (load) stacked 3D data from the camera acquisition or other exported dataset in '.cod' binary format.
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
        #          NB: the dimensions dim[0] and dim[1] are given by the camera parameters from CamType.
    
    show_Comp(X2D)
        # Function to display an individual 2D component (e.g. one component of the Mueller Matrix coeffs, or a Mask)
        # This function is based on matplotlib.
        #
        # Call: show_Comp( X2D )
        #
        # *Inputs*
        # X2D: 2D Image of shape shp2 = [dim[0],dim[1]].
    
    show_Montage(X3D)
        # Function to display the 16 components (e.g. of Mueller Matrix) in a montage form (4x4)
        # This function is based on matplotlib.
        #
        # Call: show_Montage( X3D )
        #
        # *Inputs*
        # X3D: 3D stack of 2D Components of shape shp3.
        #          The matrix X must have shape equal to [dim[0],dim[1],16].
    
    show_REls(REls)
        # Function to display the 4 Real EigenValues components of Mueller Matrix Eigen-Decomposition in a montage form (1x4)
        # This function is based on matplotlib.
        #
        # Call: show_REls( REls )
        #
        # *Inputs*
        # REls: 3D stack of 2D EigenValues Components of shape shp3 = [dim[0],dim[1],4].
        #
        # NB: The displayed Real EigenValues are sorted in a descending fashion: \lambda1 >= \lambda2 >= \lambda3 >= \lambda4

    sort_MM_REls(REls, ascendFlag=0)
        # Function to sort the (diagonal) REAL Eigen-Values Components of the Mueller Matrix Eigen-Decomposition
        # This function sorts the Real eigenvalues in a descending fashion (default)
        #
        # Call: srtREls = sort_MM_REls( REls , [ascendFlag] )
        #
        # *Inputs*
        # REls: 3D Stack of (diagonal) REAL Eigen-Values Components of shape shp3 = [dim[0],dim[1],4].
        #
        # [ascendFlag]: optional scalar boolean (0,1) as flag for ascending sorting.
        #                               (default: 0)
        #
        # * Outputs *
        # srtREls: descending sorted Eigen-Values of the Mueller Matrix decomposition: shape [dim[0],dim[1],4];
        #          srtREls[:,:,0] = \lambda1
        #          srtREls[:,:,1] = \lambda2
        #          srtREls[:,:,2] = \lambda3
        #          srtREls[:,:,3] = \lambda4
        #                                                                               with: \lambda1 >= \lambda2 >= \lambda3 >= \lambda4
    
    test_OpenMP()
        # Function to test the correct C source-code compilation linking to multi-processing libraries (openMP)
    
    test_process_MM_pipeline()
        # Function to Test the end-to-end Mueller Matrix processing pipeline for the provided testing raw data.
        # This testing data is evaluated for wavelength = 550nm.
        # NB: it is required to have run the test calibration first!
        #     In absence of test calibration, the latter will be run first.
        #
        # Call: MMParams = test_process_MM_pipeline()
        #

    validate_libmpMuelMat_testDataMAT()
        # Function to automatically run the algorithmic validation over a reference pre-computed dataset.
        # This function loads polarimetric data from a pre-computed and exported MATLAB dataset,
        # then, the re-computes the same variables with the implemented algorithmics in libmpMuelMat library.
        # Eventually the results are compared pixel-wise for all variables in the dataset and
        # statistics on computational errors are provided and displayed.
        #
        # Please set the correct path to the MAT datafile prior to running this validation.
    
    write_cod_data_X2D(X2D, output_cod_Filename, VerboseFlag=1)
        # Function to write (export) 2D data from the camera acquisitions or further processing in '.cod' binary format.
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
    
    write_cod_data_X3D(X3D, output_cod_Filename, VerboseFlag=1)
        # Function to write (export) stacked 3D data from the camera acquisitions or further processing in '.cod' binary format.
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


f. Tests and Examples

	[Testing]

	The libmpMuelMat library can be tested and validated against the state-of-the-art implementation based on MATLAB.

	1. make sure the Matlab-based Test Data file is correctly located in: ./TestData/MAT/libmpMuelMat_TestData.mat

	2. please run in the python shell:

		libmpMuelMat.validate_libmpMuelMat_testDataMAT()

	Variables are automatically loaded and the end-to-end Mueller Matrix processing pipeline is executed using libmpMuelMat.

	Computational performance is given in the printed report, for the considered Matlab-based testing dataset.

	Numerical error and deviations are provided by comparing results from libmpMuelMat and those obtained from MATLAB (reference).

	Error statistics are evaluated on a pixel-wise absolute L1 norm, and reported (min, max, avg, std).

	Similarly, for validity masks, the standard overlapping DICE score (DSC) is listed, being 1.0 the perfect match.


	[Examples]

	* End-to-end Mueller Matrix Image Processing Pipeline

	1. make sure the Scan Test Data folder and its content is correctly located in: ./TestData/Raw/Scan/

	2. the folder MUST contain the following raw binary files (.cod):
		<550_Bruit.cod> # Background Noise
		<550_Intensite.cod> # Polarimetric Intensities 

	3. please run in the python shell:

		MMParams = libmpMuelMat.test_process_MM_pipeline()

	The end-to-end Mueller Matrix Image Processing Pipeline synthetically generates the Polarisation State Matrices (A,W) for a default wavelength of 550nm,
	then, the Background Noise (<550_Bruit.cod>) and the scanned Intensities (<550_Intensite.cod>) are loaded and processed from the raw binary files.

	The full end-to-end pipeline comprises the following steps:

	i. 	Intensities and Polarisation State Matrices are used to compute the Mueller Matrix Decomposition
	ii. 	Masks of valid pixels are retrieved from its determinant, physical criterion and intensity saturation
	iii. 	Polarimetric Matrices are computed with the Lu-Chipman decomposition of the Mueller Matrix
	iv. 	Polarimetric Parameters are determined from the above matrices.

	The final results are listed in the output dictionary MMParams and can be accessed with the associated keys as:

		var = MMParam['key1']   
	or   
		var = MMParam.get('key1')

	
	The list of keys:

	'nM': normalised Mueller Matrix 
	'M11': normalising Mueller Matrix Component M(1,1)

	'Mdetmsk': mask of the pixels with negative M determinant 
	'Mphymsk': mask of the pixels satisfying the physical criterion
	'Isatmsk': mask of the pixels with saturated intensities (e.g. reflections)
	'Msk': final mask of the valid pixels obtained as logical AND of the above ones

	'Els': Real part of the Mueller Matrix EigenValues (unsorted) 

	'MD': polarimetric matrix of diattenuation
	'MR': polarimetric matrix of phase shift (retardance)
	'Mdelta': polarimetric matrix of depolarisation

	'totD': total Diattenuation of shape [dim[0],dim[1]].
	'linD': linear Diattenuation of shape [dim[0],dim[1]].
	'oriD': orientation of linear Diattenuation of shape [dim[0],dim[1]].
	'cirD': circular Diattenuation of shape [dim[0],dim[1]].

	'totR': total Phase Shift (Retardance) of shape [dim[0],dim[1]].
	'linR': linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	'cirR': circular Phase Shift (Retardance) of shape [dim[0],dim[1]].
	'oriR': orientation of linear Phase Shift (Retardance) of shape [dim[0],dim[1]].
	'oriRfull': orientation of linear Phase Shift (Retardance) Full of shape [dim[0],dim[1]].      

	'totP': total Depolarisation of shape [dim[0],dim[1]].


	NB: All Testing Data are provided for a representative square patch of 128x128 pixels
	NB: libmpMuelMat computational performance may vary upon different hardware and image size
