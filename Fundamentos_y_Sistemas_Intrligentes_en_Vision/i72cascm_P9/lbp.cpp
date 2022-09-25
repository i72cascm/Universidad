void
fsiv_lbp(const cv::Mat& img, cv::Mat& lbp){
    
    // · Documentation: https://www.bytefish.de/blog/local_binary_patterns.html
    lbp = cv::Mat::zeros(img.rows, img.cols, CV_8UC1); // We fill the image with zeros

    for (int i = 1; i < img.rows - 1; i++){
		for (int j = 1; j < img.cols - 1; j++){
			
            float center = img.at<float>(i, j); // We take our central pixel
			uchar code = 0;

			code |= ( img.at<float>(i, j - 1) > center ) << 7; // We compare the pixels
			code |= ( img.at<float>(i + 1, j - 1) > center ) << 6;
			code |= ( img.at<float>(i + 1, j) > center ) << 5;
			code |= ( img.at<float>(i + 1, j + 1) > center ) << 4;
			code |= ( img.at<float>(i, j + 1) > center ) << 3;
			code |= ( img.at<float>(i - 1, j + 1) > center ) << 2;
			code |= ( img.at<float>(i - 1, j) > center ) << 1;
			code |= ( img.at<float>(i - 1, j - 1) > center ) << 0;

			lbp.at<uchar>(i, j - 1) = code;
		}
	}
}


void
fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, const bool hist_norm){

    int histSize = 256;
	float hranges[] = {0, 256};
	const float* phranges = hranges;   
    

    cv::calcHist(&lbp, 1, 0, cv::Mat(), lbp_hist, 1, &histSize, &phranges, true, false);
  
    cv::transpose(lbp_hist, lbp_hist);

    if (hist_norm){
		cv::normalize(lbp_hist, lbp_hist, 1.0, 0.0, cv::NORM_L1);
	}

    lbp_hist.convertTo(lbp_hist, CV_32FC1);
}


void
fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, const bool hist_norm){

    int histTam = 256;
    float histog[] = {0,256};
    const float *phistog = histog;

    calcHist(&lbp,1,0,cv::Mat(),lbp_hist,1,&histTam,&phistog,true, false);

    transpose(lbp_hist,lbp_hist);

    if(hist_norm){
        normalize(lbp_hist,lbp_hist,1.0,0.0,cv::NORM_L1);
    }

    lbp_hist.converTo(lbp_hist,CV_32FC1);

}