#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// auto white balance 
// auto exposure 
// auto forcus 


int pic[2460][3360];
void OB();
void WB();
void color_interpolation();
void colormatrix();
void gamma(double);
void color();
void rgb2bmp(char *);
void edge_enhance();


int r[2460][3360];
int g[2460][3360];
int b[2460][3360];
int e[2460][3360];


unsigned short int gamma_value[1024]={
	0,1,3,5,8,9,11,12,13,14,16,17,18,20,21,22,24,25,26,28,
		29,30,32,33,34,36,37,38,39,41,42,43,45,46,47,49,50,51,53,54,
		55,57,58,59,61,62,63,64,66,67,68,70,71,72,74,75,76,78,79,80,
		82,83,84,85,87,87,88,89,89,90,91,91,92,93,93,94,95,95,96,97,
		97,98,99,99,100,101,101,102,103,103,104,105,105,106,107,107,108,108,109,110,
		110,111,112,112,113,114,114,115,116,116,117,118,118,119,120,120,121,122,122,123,
		124,124,125,126,126,127,128,128,129,129,130,130,130,130,131,131,131,132,132,132,
		133,133,133,134,134,134,135,135,135,136,136,136,137,137,137,138,138,138,139,139,
		139,140,140,140,141,141,141,142,142,142,143,143,143,144,144,144,145,145,145,146,
		146,146,147,147,147,148,148,148,149,149,149,150,150,150,151,151,151,152,152,152,
		153,153,153,154,154,154,154,155,155,155,156,156,156,157,157,157,158,158,158,159,
		159,159,160,160,160,161,161,161,162,162,162,163,163,163,164,164,164,165,165,165,
		166,166,166,167,167,167,168,168,168,169,169,169,170,170,170,171,171,171,171,171,
		172,172,172,172,172,172,173,173,173,173,173,173,174,174,174,174,174,174,175,175,
		175,175,175,175,176,176,176,176,176,176,176,177,177,177,177,177,177,178,178,178, 
		178,178,178,179,179,179,179,179,179,180,180,180,180,180,180,181,181,181,181,181,
		181,182,182,182,182,182,182,183,183,183,183,183,183,184,184,184,184,184,184,185,
		185,185,185,185,185,186,186,186,186,186,186,187,187,187,187,187,187,188,188,188,
		188,188,188,189,189,189,189,189,189,189,190,190,190,190,190,190,191,191,191,191,
		191,191,192,192,192,192,192,192,193,193,193,193,193,193,194,194,194,194,194,194,
		195,195,195,195,195,195,196,196,196,196,196,196,197,197,197,197,197,197,198,198,
		198,198,198,198,199,199,199,199,199,199,200,200,200,200,200,200,201,201,201,201,
		201,201,201,202,202,202,202,202,202,203,203,203,203,203,203,204,204,204,204,204,
		204,205,205,205,205,205,205,206,206,206,206,206,206,207,207,207,207,207,207,208,
		208,208,208,208,208,209,209,209,209,209,209,210,210,210,210,210,210,211,211,211,
		211,211,211,212,212,212,212,212,212,213,213,213,213,213,213,213,213,213,213,214,
		214,214,214,214,214,214,214,214,214,214,214,215,215,215,215,215,215,215,215,215,
		215,215,215,216,216,216,216,216,216,216,216,216,216,216,216,217,217,217,217,217,
		217,217,217,217,217,217,217,217,218,218,218,218,218,218,218,218,218,218,218,218,
		219,219,219,219,219,219,219,219,219,219,219,219,220,220,220,220,220,220,220,220,
		220,220,220,220,221,221,221,221,221,221,221,221,221,221,221,221,222,222,222,222,
		222,222,222,222,222,222,222,222,223,223,223,223,223,223,223,223,223,223,223,223,
		223,224,224,224,224,224,224,224,224,224,224,224,224,225,225,225,225,225,225,225,
		225,225,225,225,225,226,226,226,226,226,226,226,226,226,226,226,226,227,227,227,
		227,227,227,227,227,227,227,227,227,228,228,228,228,228,228,228,228,228,228,228,
		228,229,229,229,229,229,229,229,229,229,229,229,229,229,230,230,230,230,230,230,
		230,230,230,230,230,230,231,231,231,231,231,231,231,231,231,231,231,231,232,232,
		232,232,232,232,232,232,232,232,232,232,233,233,233,233,233,233,233,233,233,233,
		233,233,234,234,234,234,234,234,234,234,234,234,234,234,235,235,235,235,235,235,
		235,235,235,235,235,235,235,236,236,236,236,236,236,236,236,236,236,236,236,237,
		237,237,237,237,237,237,237,237,237,237,237,238,238,238,238,238,238,238,238,238,
		238,238,238,239,239,239,239,239,239,239,239,239,239,239,239,240,240,240,240,240,
		240,240,240,240,240,240,240,241,241,241,241,241,241,241,241,241,241,241,241,241,
		242,242,242,242,242,242,242,242,242,242,242,242,243,243,243,243,243,243,243,243,
		243,243,243,243,244,244,244,244,244,244,244,244,244,244,244,244,245,245,245,245,
		245,245,245,245,245,245,245,245,246,246,246,246,246,246,246,246,246,246,246,246,
		247,247,247,247,247,247,247,247,247,247,247,247,247,248,248,248,248,248,248,248,
		248,248,248,248,248,249,249,249,249,249,249,249,249,249,249,249,249,250,250,250,
		250,250,250,250,250,250,250,250,250,251,251,251,251,251,251,251,251,251,251,251,
		251,252,252,252,252,252,252,252,252,252,252,252,252,253,253,253,253,253,253,253,
		253,253,253,253,253,254,254,254,254,254,254,254,254,254,254,254,254,255,255,255,
		255,255,255,255
}; 



int main(int argc,char *argv[])
{

	for(int k=1;k<argc;k++)
	{
		FILE *fp;				// �}��
		fp=fopen(argv[k],"rb");	//
		fseek(fp,862144,SEEK_SET);
		for(int i=0;i<2460;i++)
			for(int j=0;j<3360;j++)
			{
				pic[i][j]=0;
				fread(pic[i]+j,1,1,fp);
				pic[i][j]<<=8;
				fread(pic[i]+j,1,1,fp);
			}
		fclose(fp);	

		OB();
		printf("whp\n");
		WB();
		color_interpolation();
		colormatrix();
		gamma(1.06);
		//edge_enhance();
        
		rgb2bmp(argv[k]);
	
	
	
	}

	return 0;
}



void OB()
{
	int ob_sum = 0;
	int ob_avg = 0;
	int count = 0,i,j;
	
	//OB for E region
	ob_sum = 0;
	count = 0;
	
	for(i = 0; i <2460 ; i = i+2)
	{
		for(int j=0 ; j<5; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
		for(j = 3294 ; j<3343; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
	}

	ob_avg = ob_sum / count;
	for(i = 0; i <2460 ; i = i+2)
		for(int j = 6 ; j<3293; j = j+2)
		{
			if(pic[i][j] > ob_avg)
				pic[i][j] = pic[i][j] - ob_avg;
			else
				pic[i][j]=0;
		}
	
	ob_sum = 0;
	count = 0;



	//OB for R region
	for(i = 0; i <2460 ; i = i+2)
	{
		for(j = 1 ; j<5; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
		for(j = 3293 ; j<3343; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
	}
	ob_avg = ob_sum / count;
	for(i = 0; i <2460 ; i = i+2)
		for(int j = 5 ; j<3293; j = j+2)
		{
			if(pic[i][j] > ob_avg)
				pic[i][j] = pic[i][j] - ob_avg;
			else
				pic[i][j]=0;
		}
	
	//OB for B region
	ob_sum = 0;
	count = 0;
	
	for(i = 1; i <2460 ; i = i+2)
	{
		for(int j = 0 ; j<5; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
		for(j = 3294 ; j<3343; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
	}
	ob_avg = ob_sum / count;
	for(i = 1; i <2460 ; i = i+2)
		for(int j = 6 ; j<3293; j = j+2)
		{
			if(pic[i][j] > ob_avg)
				pic[i][j] = pic[i][j] - ob_avg;
			else
				pic[i][j]=0;
		}

	//OB for G region
	ob_sum = 0;
	count = 0;
	for(i = 1; i <2460 ; i = i+2)
	{
		for(int j = 1 ; j<5; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
		for(j = 3293 ; j<3343; j = j+2)
		{
			ob_sum = ob_sum + pic[i][j];
			count++;
		}
	}
	ob_avg = ob_sum / count;
	for(i = 1; i <2460 ; i = i+2)
		for(int j = 5 ; j<3293; j = j+2)
        {
			if(pic[i][j] > ob_avg)
				pic[i][j] = pic[i][j] - ob_avg;
			else
				pic[i][j]=0;
		}
	double r_equal,g_equal,b_equal,e_equal,Y_equal,Cr_equal,Cb_equal;
    double Y_avg, Cr_avg,Cb_avg,aad_Cr,aad_Cb;	
    double a_avg=0,g_avg=0,b_avg=0;
	FILE *green;
	green=fopen("green.txt","w+t");
   
    
    

    for( i=0;i<2458;i+=2)
	  {
		  for(j=5;j<3293;j+=2)
		  {
              count++;
              r_equal=pic[i][j];
              a_avg+=r_equal;
              b_equal=pic[i+1][j+1];
              b_avg+=b_equal;
              g_equal=pic[i+1][j];
              g_avg+=g_equal;
              fprintf(green,"%f ",g_equal);

			  


          }
      }
      fclose(green);
    printf("avg~~~*****,%f %f %f  \n\n",a_avg,g_avg,b_avg);
    a_avg=a_avg/count;
    g_avg=g_avg/count;
    b_avg=b_avg/count;
    printf("avg~~~,%f %f %f  \n\n",a_avg,g_avg,b_avg);
	printf("Optical Black ---OK!\n");

}


void WB(){

    int i,j;

    double r_equal,g_equal,b_equal,e_equal,Y_equal,Cr_equal,Cb_equal;
    double Y_avg=0, Cr_avg=0,Cb_avg=0,aad_Cr=0,aad_Cb=0;
    double count=0;
    double Y_max=0;
    double a_avg=0,g_avg=0,b_avg=0;
    double add_crr[12],add_cbb[12];
    double crr_avg[12],cbb_avg[12],countt[12];
    int caser,casec,pos,posn=0;
    for(i=0;i<2458;i+=2)
	  {
		  for(j=5;j<3350;j+=2)
		  {
            count++;
            r_equal=pic[i][j];
            a_avg+=r_equal;
            b_equal=pic[i+1][j+1];
            b_avg+=b_equal;
            g_equal=pic[i+1][j];
            g_avg+=g_equal;
            

            Y_equal=(0.213*r_equal)+(0.715*g_equal)+(0.072*b_equal);
			Cb_equal=(-0.117*r_equal)-(0.394*g_equal)+(0.511*b_equal)+8192;
			Cr_equal=(0.511*r_equal)-(0.464*g_equal)-(0.047*b_equal)+8192;
			  //Y_equal=(0.299*r_equal)+(0.587*g_equal)+(0.114*b_equal);
              if(Y_equal>Y_max) Y_max=Y_equal;

              Y_avg+=Y_equal;
			  //Cr_equal=(0.500*r_equal)-(0.4187*g_equal)-(0.0813*b_equal);
              Cr_avg+=Cr_equal;
			  //Cb_equal=(-0.1687*r_equal)-(0.3313*g_equal)+(0.500*b_equal);
              Cb_avg+=Cb_equal;


          }
      }
       
    a_avg=a_avg/count;
    g_avg=g_avg/count;
    b_avg=b_avg/count;
    printf("avg~~~,%f %f %f  \n\n",a_avg,g_avg,b_avg);
    Y_avg=Y_avg/count;
    Cb_avg=Cb_avg/count;
    Cr_avg=Cr_avg/count;
    printf("%f Yavg,%f cr,%f cb \n\n",Y_avg,Cb_avg,Cr_avg);
    printf("count %f\n",count);
    for(i=0;i<2458;i+=2)
	  {
		    for(j=5;j<3293;j+=2)
		  {
              
            r_equal=pic[i][j];
            b_equal=pic[i+1][j+1];
            g_equal=pic[i+1][j];
			Y_equal=(0.213*r_equal)+(0.715*g_equal)+(0.072*b_equal);
			Cb_equal=(-0.117*r_equal)-(0.394*g_equal)+(0.511*b_equal)+8192;
			Cr_equal=(0.511*r_equal)-(0.464*g_equal)-(0.047*b_equal)+8192;
            //Cr_equal=(0.500*r_equal)-(0.4187*g_equal)-(0.0813*b_equal);
            aad_Cr+= abs(Cr_avg-Cr_equal );
			  
            //Cb_equal=(-0.1687*r_equal)-(0.3313*g_equal)+(0.500*b_equal);
            aad_Cb+= abs(Cb_avg-Cb_equal );
    
          }
      }
    aad_Cr=aad_Cr/count;
    aad_Cb=aad_Cb/count;
    printf("AAD: %f \n %f\n",aad_Cr,aad_Cb);
    printf("count %f",count);


    double Y_hist[16384];
    for(i=0;i<16384;i++){Y_hist[i]=0;}
    int select_num=0;

    for(i=0;i<2458;i+=2)
	{
		for(j=5;j<3293;j+=2)
		{
            r_equal=pic[i][j];
            b_equal=pic[i+1][j+1];
            g_equal=pic[i+1][j];
			
            Y_equal=(0.213*r_equal)+(0.715*g_equal)+(0.072*b_equal);
			Cb_equal=(-0.117*r_equal)-(0.394*g_equal)+(0.511*b_equal)+8192;
			Cr_equal=(0.511*r_equal)-(0.464*g_equal)-(0.047*b_equal)+8192;

			// Y_equal=(0.299*r_equal)+(0.587*g_equal)+(0.114*b_equal);
			// Cr_equal=(0.500*r_equal)-(0.4187*g_equal)-(0.0813*b_equal);
			// Cb_equal=(-0.1687*r_equal)-(0.3313*g_equal)+(0.500*b_equal);
                if(Cr_avg>0 && Cb_avg>0){
                    if( abs( Cb_equal-Cb_avg-aad_Cb ) < 1.5* aad_Cb) 
                    if(abs (Cr_equal-1.5*Cr_avg-aad_Cr) < 1.5* aad_Cr){
                        Y_hist[(int)Y_equal]+=1;
                        select_num++;
                    }
                }else if(Cb_avg>0 && Cr_avg<0){
                    if( abs( Cb_equal-Cb_avg-aad_Cb ) < 1.5* aad_Cb) 
                    if(abs (Cr_equal-1.5*Cr_avg+aad_Cr) < 1.5* aad_Cr){
                        Y_hist[(int)Y_equal]+=1;
                        select_num++;
                    }

                }else if(Cb_avg<0 && Cr_avg>0){

                     if( abs( Cb_equal-Cb_avg+aad_Cb ) < 1.5* aad_Cb) 
                     if(abs (Cr_equal-1.5*Cr_avg-aad_Cr) < 1.5* aad_Cr){
                        Y_hist[(int)Y_equal]+=1;
                        select_num++;
                    }

                }else if (Cb_avg<0 && Cr_avg<0){

                    if( abs( Cb_equal-Cb_avg+aad_Cb ) < 1.5* aad_Cb) 
                    if(abs (Cr_equal-1.5*Cr_avg+aad_Cr) < 1.5* aad_Cr){
                        Y_hist[(int)Y_equal]+=1;
                        select_num++;
                    }


                }
          }
          
      }
      double y_num=0;
      printf("select num%d \n",select_num);
      int y;
      for(y=0;y<16384;y++)
	  {
		  y_num+=Y_hist[y];
          if(y_num>=select_num*0.95) break;		  
	  }
      double y_lim;
      y_lim=y;
      printf("ylim %d\n",y);

    
    double r_white=0,g_white=0,b_white=0,e_white=0;
    double white_num=0;
    for(i=0;i<2458;i+=2)
	  {
		for(j=5;j<3293;j+=2)
		{
              
            r_equal=pic[i][j];
            b_equal=pic[i+1][j+1];
            g_equal=pic[i+1][j];  
            e_equal=pic[i][j+1]; 
			Y_equal=(0.213*r_equal)+(0.715*g_equal)+(0.072*b_equal);
			// Cb_equal=(-0.117*r_equal)-(0.394*g_equal)+(0.511*b_equal)+8192;
			// Cr_equal=(0.511*r_equal)-(0.464*g_equal)-(0.047*b_equal)+8192;
			// Y_equal=(0.299*r_equal)+(0.587*g_equal)+(0.114*b_equal);
              
			if(Y_equal> y_lim){
                r_white+=r_equal;
                g_white+=g_equal;
                b_white+=b_equal;
                e_white+=e_equal;
                white_num+=1;
            }
          }
      }

     printf("avage white r:%f\n g:%f \n b:%f \n e:%f\n ",r_white,g_white,b_white,e_white);
    r_white/=white_num;
    g_white/=white_num;
    b_white/=white_num;
    e_white/=white_num;
    printf("white num %f\n\n",white_num);
    printf("avage white r:%f\n g:%f \n b:%f \n e:%f\n ",r_white,g_white,b_white,e_white);
    printf("Y max %f ",Y_max);
    double r_gain,g_gain,b_gain,e_gain;
    r_gain=Y_max/r_white;
    g_gain=Y_max/g_white;
    b_gain=Y_max/b_white;
    e_gain=Y_max/e_white;
    printf("gain %f %f %f %f\n ",r_gain,g_gain,b_gain,e_gain);

    for(i=0;i<2458;i+=2)
	{
		for(j=5;j<3350;j+=2)
		{
            pic[i][j]*=r_gain;//R
			pic[i+1][j+1]*=b_gain;//B
			pic[i+1][j]*=g_gain;//G
			pic[i][j+1]*=e_gain; //E
          }
          
    }

 
        
    
    printf("AWB finish\n");

}































void color_interpolation()  //rgbe
{
	int i,j;
	
	//R region

	for( i = 0; i <2460 ; i = i+2)
		for( j = 5 ; j<3355; j = j+2)
		{
			r[i][j] = pic[i][j];			
			g[i][j] = (( pic[i-1][j] + pic[i+1][j] )+ (pic[i][j-1]+pic[i][j+1])/2)/3; //g+E(cyan=G+B)
			b[i][j] = ( pic[i-1][j-1] + pic[i-1][j+1] + pic[i+1][j-1] + pic[i+1][j+1]+ (pic[i][j-1]+pic[i][j+1])/2)/5;
		}

	//G region

	for( i = 1; i <2460 ; i = i+2)
		for( j = 5 ; j<3293; j = j+2)
        {
			g[i][j] = pic[i][j];			
			r[i][j] = ( pic[i-1][j] + pic[i+1][j] )/2;
			b[i][j] = ( pic[i][j-1] + pic[i][j+1]+( pic[i-1][j-1] + pic[i-1][j+1] + pic[i+1][j-1] + pic[i+1][j+1])/2)/4;
		}
		
	//E region

	for( i = 0; i <2460 ; i = i+2)
		for( j = 6 ; j<3293; j = j+2)
		{
		
				b[i][j] = ( 2*pic[i-1][j] + 2*pic[i+1][j]+pic[i][j] )/5;
				g[i][j] = ( 2*pic[i-1][j-1] +2* pic[i-1][j+1] +2* pic[i+1][j-1] +2* pic[i+1][j+1]+pic[i][j])/9;
				r[i][j] = ( pic[i][j-1] + pic[i][j+1] )/2;
		}

	//B region

	for( i = 1; i <2460 ; i = i+2)
		for( j = 6 ; j<3293; j = j+2)
		{
			b[i][j] = pic[i][j];			
			r[i][j] = ( pic[i-1][j-1] + pic[i-1][j+1] + pic[i+1][j-1] + pic[i+1][j+1] )/4;
			g[i][j] = ( pic[i][j-1] + pic[i][j+1] +(pic[i-1][j]+pic[i+1][j])/2)/3;
		}
	
	printf("new Color interpolation ---OK!\n");

}


void colormatrix()
{
 //
 // [R']=[ 1+sa+sb   -sa       -sb     ][R]
 // [G']=[ -sc       1+sc+sd   -sd     ][G]
 // [B']=[ -se       -sf       1+se+sf ][B]  
 // 	 
	unsigned short int i,j;
	double temp_r,temp_g,temp_b;
	//double sa=0.265625,sb=0.17;
	//double sc=0.21,sd=0.21;
	//double se=0.19,sf=0.19;
	
	for(i=0;i<2460;i++){
		for(j=0;j<3360;j++){
			temp_r=r[i][j];
			temp_g=g[i][j];
			temp_b=b[i][j];
			
			//r[i][j]=(1.0+sa+sb)*temp_r - (sa)*temp_g - (sb)*temp_b;
			r[i][j]=(double)((1.2665625)*temp_r+(-0.28125)*temp_g+(0.0)*temp_b);//paul
            //r[i][j]=(double)((6.3329)*temp_r+(-2.7900)*temp_g+(1.5002)*temp_b);       
			if (r[i][j]>16360)//1022.5*16
				r[i][j]=16360;
			else if (r[i][j]<0)
				r[i][j]=0;
			
			//g[i][j]=(1.0+sc+sd)*temp_g - (sc)*temp_r   - (sd)*temp_b;
			g[i][j]=(double)((-0.1875)*temp_r+(1.203125)*temp_g+(-0.046875)*temp_b);//paul
            //g[i][j]=(double)((0.1362)*temp_r+(2.6597)*temp_g+(0.0751)*temp_b);
			if (g[i][j]>16360)//1022.5*16
				g[i][j]=16360;
	        else if (g[i][j]<0)
				g[i][j]=0;
			
			//b[i][j]=(1.0+se+sf)*temp_b - (se)*temp_r - (sf)*temp_g ;
			b[i][j]=(double)((-0.078125)*temp_r+(-0.296875)*temp_g+(1.359375)*temp_b);//paul
            //b[i][j]=(double)((1.2656)*temp_r+(-1.5919)*temp_g+(4.7861)*temp_b);
			if (b[i][j]>16360)//1022.5*16
				b[i][j]=16360;
			else if (b[i][j]<0)
				b[i][j]=0;
		}
	}
	printf("colormatrix ---OK!\n");
}


void gamma(double gamma_cur)
{
    int i,j;
	for(i=0;i<2460;i++)
	{
		for(j=0;j<3360;j++)
		{
			if (pow(r[i][j],gamma_cur)>16383){
				r[i][j]=16383;
			}else{
			    r[i][j]=pow(r[i][j],gamma_cur);
			}

			if (pow(g[i][j],gamma_cur)>16383){
				g[i][j]=16383;
			}else{
				g[i][j]=pow(g[i][j],gamma_cur);
			}

			if (pow(b[i][j],gamma_cur)>16383){
				b[i][j]=16383;
			}else{
				b[i][j]=pow(b[i][j],gamma_cur);
			}


			r[i][j]=gamma_value[r[i][j]/16];//16=2^14/2^10
			g[i][j]=gamma_value[g[i][j]/16];
			b[i][j]=gamma_value[b[i][j]/16];  
		}
	}
	
	printf("gamma ---OK!\n");


}


void rgb2bmp(char *name)
{

	FILE *fp;
	int zero=0;
	char filename[100];
	strcpy(filename,name);
	strcat(filename,".bmp");

	fp=fopen(filename,"wb");

	fwrite(&"BM",1,2,fp);	
	int temp=54+3264*2448*3;
	fwrite(&temp,4,1,fp);
	
	for(int bmpcount=0;bmpcount<4;bmpcount++)//reserved
		fwrite(&zero,1,1,fp);

	temp=54;//start address of datas
	fwrite(&temp,4,1,fp);
	temp=40;//size of [0E-35]
	fwrite(&temp,1,1,fp);
	fwrite(&zero,1,1,fp);
	fwrite(&zero,1,1,fp);
	fwrite(&zero,1,1,fp);
	int width=3264;//width
	fwrite(&width,4,1,fp);
	int height=2448;//height
	fwrite(&height,4,1,fp);
	temp=1;//color planes
	fwrite(&temp,2,1,fp);
	temp=24;//bits/pixel
	fwrite(&temp,2,1,fp);
	fwrite(&zero,4,1,fp);//Compression format
	
	temp=23970816;//data size->3264*2448*3
	fwrite(&temp,4,1,fp);
	fwrite(&zero,4,1,fp);//width pixels/meter
	fwrite(&zero,4,1,fp);//height pixels/meter
	fwrite(&zero,2,1,fp);//color tables
	fwrite(&zero,1,1,fp);//
	fwrite(&zero,1,1,fp);
	fwrite(&zero,4,1,fp);//color indexes
//body
	for(int bmpi=2453;bmpi>=6;bmpi--)
		for(int bmpj=17;bmpj<3281;bmpj++)
		{
		    fwrite(&(b[bmpi][bmpj]),1,1,fp);
			fwrite(&(g[bmpi][bmpj]),1,1,fp);
			fwrite(&(r[bmpi][bmpj]),1,1,fp);
		}
	fclose(fp);
	printf("%s output finished.\n",name);
}
