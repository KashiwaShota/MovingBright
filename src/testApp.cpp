#include "testApp.h"
#include "ofMath.h"

ofVideoGrabber vidGrabber;
ofImage img;
int camWidth, camHeight;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);//RGB背景色
	ofEnableSmoothing();//スムージング開始
	ofSetFrameRate(10);//フレームレート設定
	//キャプチャする画像のサイズを指定
	camWidth = 450;//キャプチャ画面の幅
	camHeight = 300;//キャプチャ画面の高さ
	vidGrabber.setVerbose(true);//使用可能のデバイスを探す
	vidGrabber.initGrabber(camWidth, camHeight);//インターフェイスをデバックに役立つ
}

//--------------------------------------------------------------
void testApp::update(){
	//キャプチャする
	vidGrabber.grabFrame();//sequence grabbeから新しいデータを得る為に定期的に呼び出す
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);//描画色(黒)
	vidGrabber.draw(20,20);//20,20から描画する
	
	//現在のフレームのピクセル配列,RGB[width*height*3]のポインタを返します。
	unsigned char * pixels = vidGrabber.getPixels();



	//前フレームのRGBを配列に格納
	int prevRGB[405000];
	for(int i = 0; i < 405000; i++){
		prevRGB[i] = pixels[i];
	}



	//画像処理
	for(int i = 0; i < camHeight; i++){
		for(int j = 0; j < camWidth; j++){
			int p = i * camWidth * 3 + j * 3;
			/*
			//反転
			pixels[p] = 255-pixels[p];
			pixels[p + 1] = 255-pixels[p + 1];
			pixels[p + 2] = 255-pixels[p + 2];
			*/



			//以下、追加したHSVへの変換
			//RGBからHSVへ
			int max, min;//最大値と最小値を格納する変数
			//int len = pixels.length();
			int hsv[405000];//hsvの配列を宣言
			//float max = Math.mas(pixels[p], Math.max(pixels[p + 1], pixels[p + 2]));
			//最大値の決定
			if(pixels[p] >= pixels[p + 1]){
				max = pixels[p];
			}else{
				max = pixels[p + 1];
			}
			if(pixels[p + 2] > max){
				max = pixels[p + 2];
			}
			//float min = Math.min(pixels[p], Math.min(pixels[p + 1], pixels[p + 2]));
			//最小値
			if(pixels[p] <= pixels[p + 1]){
				min = pixels[p];
			}else{
				min = pixels[p + 1];
			}
			if(pixels[p + 2] < min){
				max = pixels[p + 2];
			}
			//色相(hus)の決定
			if(max == min){
				hsv[p] = 0;
			}else if(max == pixels[p]){
				hsv[p] = (60 * (pixels[p + 1] - pixels[p + 2]) / (max - min) + 360) % 360;
			}else if(max == pixels[p + 1]){
				hsv[p] = (60 * (pixels[p + 2] - pixels[p]) / (max - min)) + 120;
			}else if(max == pixels[p + 2]){
				hsv[p] = (60 * (pixels[p] - pixels[p + 1]) / (max - min)) + 240;
			}
			//彩度(saturation)の決定
			if(max == 0){
				hsv[p + 1] = 0;
			}else{
				hsv[p + 1] = (255 * ((max - min) / max));
			}
			//明度(value)の決定
			hsv[p + 2] = max;



			//HSVに手を加える
			hsv[p + 1] = 0;//色彩を0にしてモノクロ化
			//フレームの比較
			/*
			int varR = prevRGB[p] - pixels[p];//赤の変化量
			int varG = prevRGB[p + 1] - pixels[p + 1];//緑の変化量
			int varB = prevRGB[p + 2] - pixels[p + 2];//青の変化量
			hsv[p + 1] = hsv[p + 1] varR varG varB;//明度の増減式
			*/



			//HSVからRGBへ
			float f;
			int hoge, b, q, t,
			//a = (int)Math.floor(hsv[p] / 60.0f) % 6;
			hoge = (hsv[p] / 60) % 6;
			//f = (float)(hsv[p] / 60.0f) - (float)Math.floor(hsv[p] / 60.0f);
			f = (hsv[p] / 60) - (hsv[p] / 60);
  			//b = (int)Math.round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f)));
			b = (hsv[p + 2] * (1 - (hsv[p + 1] / 255))) + 0.5;
			//q = (int)Math.round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f) * f));
			q = (hsv[p + 2] * (1 - (hsv[p + 1] / 255) * f)) + 0.5;
			//t = (int)Math.round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f) * (1.0f - f)));
			t = (hsv[p + 2] * (1 - (hsv[p + 1] / 255) * (1 - f))) + 0.5;
			//場合に合わせてRGBを決定する
			switch(hoge){
				case 0: pixels[p] = hsv[p + 2]; pixels[p + 1] = t;          pixels[p + 2] = b;          break;
				case 1: pixels[p] = q;          pixels[p + 1] = hsv[p + 2]; pixels[p + 2] = b;          break;
				case 2: pixels[p] = b;          pixels[p + 1] = hsv[p + 2]; pixels[p + 2] = t;          break;
				case 3: pixels[p] = b;          pixels[p + 1] = q;          pixels[p + 2] = hsv[p + 2]; break;
				case 4: pixels[p] = t;          pixels[p + 1] = b;          pixels[p + 2] = hsv[p + 2]; break;
				case 5: pixels[p] = hsv[p + 2]; pixels[p + 1] = b;          pixels[p + 2] = q;          break;
			}
		}
	}
	//処理後の画像の描画
	img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
	img.draw(20, 330);//20,330から画像処理したモノを描画する
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}