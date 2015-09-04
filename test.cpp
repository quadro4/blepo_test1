
//VS2012 update4 with blepo library




#include <afxwin.h>  // necessary for MFC to work properly
#include "../../src/blepo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace blepo;
//using namespace blepo_ex;



/*
	Tester: test whether the filename exists.


	return 0: file exists
	return 1: file do not exists

*/
int file_existence(const CString filename)
{
	
	if (NULL == fopen(filename,"r") )	
		return 1;
	
	else
		return 0;
}

/*
	c. Creates a synthetic grayscale image of the same size as filename1 with each pixel 
	in a 100x100 square region centered in the image set to the value 255, 
	and all other pixels set to 0.  If filename1 is smaller than 100x100, 
	the application sets all pixels in the synthetic image to 255.

	return 0: Done
	return 1: Error in size

*/
int Homework1_ccube(const ImgBgr& img_in , ImgGray* img_out)
{
	//Got img_in's height and width and save it in int
	int size_pattern = 0;
	int tmp_h = img_in.Height();
	int tmp_w = img_in.Width();

	//Resize img_out and make it equal with img_in 
	img_out->Reset( img_in.Width(), img_in.Height() );
	Set(img_out, 0);

	if(	img_in.Height() > 100 && img_in.Width() > 100 )
	{
		size_pattern = 1;
	}
	else if( img_in.Height() < 101 && img_in.Width() > 100 )
	{
		size_pattern = 2;
	}
	else if( img_in.Height() > 101 && img_in.Width() < 100 )
	{
		size_pattern = 3;
	}
	else if( img_in.Height() < 101 && img_in.Width() < 101)
	{
		size_pattern = 4;
	}
	else
	{
		return 1; //Error in size
	}
		
	
	//Scan all pixels
	for(int y=0; y < img_in.Height(); y++)
	{
		for(int x=0; x < img_in.Width(); x++)
		{
			
			
			//if img_in > 100X100 size
			//find cental point and scale 100*100 centered rect
			if( 
				(size_pattern == 1)
				&&(  (y>= tmp_h/2-50 ) && ( y <= tmp_h/2+49 ) ) 
				&&(  (x>= tmp_w/2-50 ) && ( x <= tmp_w/2+49 ) ) 
			  )
			{   (*img_out)(x,y) = 255;	} //meet requirement and draw white

		
			
			//if img_in Height<100 and Width>100
			else if( 
				(size_pattern == 2)
				&&(  (x>= tmp_w/2-50 ) && ( x <= tmp_w/2+49 ) ) 
			  )
			{   (*img_out)(x,y) = 255;	} //meet requirement and draw white

		


			//if img_in Height>100 and Width<100
			else if( 
				(size_pattern == 3)
				&&(  (y>= tmp_h/2-50 ) && ( y <= tmp_h/2+49 ) )  
			  )
			{   (*img_out)(x,y) = 255;	} //meet requirement and draw white

		


			//if img_in size < 100X100
			else if( size_pattern == 4 )
			{   (*img_out)(x,y) = 255;	} //meet requirement and draw white

			else
			{	(*img_out)(x,y) = 0;	}//otherwise, draw black

		}
	}
	return 0;//Func done
		
}



/*
	f. Masks the BGR image with the grayscale image just loaded. That is, every pixel in the BGR image 
	whose corresponding pixel in the grayscale image is 0 is set to black, (0,0,0), while all other pixels are left untouched. 
	If the BGR and grayscale images are different sizes, then an error is printed. 


	return 0: Done
	return 1: Error in size

*/
int Homework1_mask(const ImgBgr& img_in, const ImgGray& img_mask , ImgBgr* img_out)
{
	
	
	
	//if img_in and img_mask have different size, stop proc and output 0 
	if( IsSameSize(img_in, img_mask) == 0)
	{ 
		return 1;
	}	

	//if img_in and img_mask have the same size, do mask and output 1
	else
	{
		//Resize img_out and make it equal with img_in 
		img_out->Reset( img_in.Width(), img_in.Height() );
		//Copy img_in to img_out
	    *img_out = img_in;

		//Scan all pixels
		for(int y=0; y < img_in.Height(); y++)
		{
			for(int x=0; x < img_in.Width(); x++)
			{
				//When pixel in mask showing black, the same pixel in img_out shows black
				if( img_mask(x,y) == 0   )
				{ 
					(*img_out)(x,y).b = 0;
					(*img_out)(x,y).g = 0;
					(*img_out)(x,y).r = 0;
				}	

				////When pixel in mask showing white, the same pixel in img_out is untouched and copied from img_in
				//else
				//{
				//	//(*img_out)(x,y).b = img_in(x,y).b;
				//	//(*img_out)(x,y).g = img_in(x,y).g;
				//	//(*img_out)(x,y).r = img_in(x,y).r;
				//}
			
			}
		}
		return 0;//Func Done
	}
	
}








   



int main(int argc, const char* argv[], const char* envp[])
{

	// Initialize MFC and return if failure
	HMODULE hModule = ::GetModuleHandle(NULL);
	if (hModule == NULL || !AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
	{
		printf("Fatal Error: MFC initialization failed (hModule = %x)\n", hModule);
		return 1;
	}
	

	/**************************************************************************************************/	
	//input test
	//input test
	//input test
	/**************************************************************************************************/
	//Command parameters print and count test 
	printf("argc = %d\n", argc);
	for (int i=0; i<argc ; i++) 
	{
		printf("argv[%d]=%s\n\n", i, argv[i]);
	}
	
	
	if( argc<3 )	
	{
		printf("Error: unspecified command parameters\n");
		return 1;
	}

	

	//filename1 input a file as the initial image
	//filename2 output a file as the mask or syn image with initail image
	//filename3 input a file as the mask
	//images_path is solid 

	CString filename1 = argv[1];
	CString filename2 = argv[2];
	CString filename3 = argv[3];
	CString images_path="../../images/";


	if(1 == file_existence( (images_path+filename1) ) ) 
	{
	
		printf("Error: Cannot Open ");
		printf("Path=%s\n",images_path+filename1);
		return 1;
	}

	if(0 == file_existence( (images_path+filename2) ) ) 
	{
	
		printf("Warning: File exists on filename 2");
		printf("Path=%s\n",images_path+filename2);
		//return 1;
	}

	if(0 == file_existence( (images_path+filename3) ) ) 
	{
	
		printf("Warning: File exists on filename 3");
		printf("Path=%s\n",images_path+filename3);
		//return 1;
	}





	
	//Judge filename2's type, which should not be jpg or JPG, by searching continuing .jpg and .JPG in the filename2
	//also it is better to find the magic word of pic format
	if( 
		 (  ( ( filename2.GetLength()-filename2.ReverseFind( '.' ) ) ==4 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'j' ) ) ==3 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'p' ) ) ==2 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'g' ) ) ==1 )
		 )

	   ||(  ( ( filename2.GetLength()-filename2.ReverseFind( '.' ) ) ==4 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'J' ) ) ==3 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'P' ) ) ==2 )
		  &&( ( filename2.GetLength()-filename2.ReverseFind( 'G' ) ) ==1 )
		 )
	 )

	{
		printf("Warning: filename2 cannot be .jpg or .JPG\n\n");
	}
	

	/**************************************************************************************************/
	/**************************************************************************************************/
	/**************************************************************************************************/






	// a. Initial opt
	printf("Start:\na: ");
	//Image/Fig declaration
	ImgBgr img1;
	ImgBgr img4;
	ImgGray img2;
	ImgGray img3;
	Figure fig1, fig2, fig3, fig4;



	// b. Load Img cat.pgm and show it
	filename1=images_path+filename1;
	Load(filename1, &img1);
	//Judge Loading status
	if( ( img1.Height()==0 ) && ( img1.Width()==0 ) )
	{
		printf("b. Error: Loading filename1 failure\n");
	}
	else
	{
		printf("b. filename1 has been loaded\n");
	}
	// Display cat.pgm
	fig1.Draw(img1);
	fig1.SetTitle("Load Filename 1");
	printf("   Path=%s\n",filename1);
	printf("   The size of filename1 is ");
	printf("%d,%d\n", img1.Width(), img1.Height() );
	printf("   Figure1: Display filename1 \n\n");
	
	

	//c. gain a synthetic image from img1 and show it
	if( Homework1_ccube(img1 , &img2) == 1 )
	{
		printf("c. Error: Input img's size\n");
	}
	else
	{
		printf("c. Action: synthetic image done\n");
	}
	//Display synthetic image
	fig2.Draw(img2);
	fig2.SetTitle("Display synthetic image");
	printf("   The size of synthetic image is ");
	printf("%d,%d\n", img2.Width(), img2.Height() );
	printf("   Figure2: Display synthetic image\n\n");

	

	//d. Save img2 as a file ( cube12138.pgm )
	filename2=images_path+filename2;
	Save(img2, filename2, "pgm");
	printf("d. synthetic image has been saved as filename2 \n");
	printf("   Path=%s\n\n",filename2);


	
	//e. load filename3 as img3 
	filename3=images_path+filename3;
	Load(filename3, &img3);
	//Judge Loading status
	if( ( img3.Height()==0 ) && ( img3.Width()==0 ) )
	{
		printf("e. Error: Loading filename3 failure\n");
	}
	else
	{
		printf("e. filename3 has been loaded \n");
		printf("   Path=%s\n",filename3);

	}
	printf("   The size of filename3 is ");
	printf("%d,%d\n", img3.Width(), img3.Height() );
	// Display reloaded cube12138.pgm
	fig3.Draw(img3);
	fig3.SetTitle("Display filename 3");
	printf("   Figure3: Display filename3 \n\n");




	//f. add a mask in filename1
	if( Homework1_mask(img1, img3 , &img4) == 1 )
	{
		printf("f. Error: Mask process halts, Non-equal size\n");
	}
	else
	{
		printf("f. Action: Mask done.\n");
		//g. Display filename1 with mask filename3
		fig4.Draw(img4);
		fig4.SetTitle("Display filename 1 with mask filename 3");
	    printf("   Figure4: Display filename1 with mask filename3 \n");
	}





	// Loop forever until user presses Ctrl-C in terminal window.
	EventLoop();
	return 0;
	


}



