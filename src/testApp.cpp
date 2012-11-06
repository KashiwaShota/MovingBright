#include "testApp.h"

ofVideoGrabber vidGrabber;
int hsv[405000];//HSVの配列を宣言(int = hsv[p])
/*
hsv[p] = 色相(hus)
hsv[p + 1] = 彩度(saturation)
hsv[p + 2] = 明度(value)
*/
/*
int max, min;//最大値と最小値を格納
これだけ此処で宣言するとあいまいな変数だと言われる
*/
int preValue[];//前フレーム明度をの配列を宣言
float varAbs;//絶対値を格納
//HSVからRGBへ変換時に使用する変数
float f;
int hoge, b, q, t;
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
	vidGrabber.draw(20,20);//元映像を描画する
	//現在のフレームのピクセル配列,RGB[width*height*3]のポインタを返す
	unsigned char * pixels = vidGrabber.getPixels();
	for(int i = 0; i < camHeight; i++){
		for(int j = 0; j < camWidth; j++){
			int p = i * camWidth * 3 + j * 3;
			//RGBからHSVへ
			int max, min;//最大値と最小値を格納
			//最大値(max)の決定
			if(pixels[p] >= pixels[p + 1]){
				max = pixels[p];
			}else{
				max = pixels[p + 1];
			}
			if(pixels[p + 2] > max){
				max = pixels[p + 2];
			}
			//最小値(min)の決定
			if(pixels[p] <= pixels[p + 1]){
				min = pixels[p];
			}else{
				min = pixels[p + 1];
			}
			if(pixels[p + 2] < min){
				max = pixels[p + 2];
			}
			//色相(hsv[p])の決定
			if(max == min){
				hsv[p] = 0;
			}else if(max == pixels[p]){
				hsv[p] = (60 * (pixels[p + 1] - pixels[p + 2]) / (max - min) + 360) % 360;
			}else if(max == pixels[p + 1]){
				hsv[p] = (60 * (pixels[p + 2] - pixels[p]) / (max - min)) + 120;
			}else if(max == pixels[p + 2]){
				hsv[p] = (60 * (pixels[p] - pixels[p + 1]) / (max - min)) + 240;
			}
			//彩度(hsv[p + 1])の決定
			if(max == 0){
				hsv[p + 1] = 0;
			}else{
				hsv[p + 1] = (255 * ((max - min) / max));
			}
			//明度(hsv[p + 2])の決定
			hsv[p + 2] = max;
			
			
			
			//HSVに手を加える
			hsv[p + 1] = 0;//色彩を0にしてモノクロ化
			//前フレームと現在フレームの明度比較
			/*
			//明度配列の格納する場所を求める
			if(preValue[] >= hsv[p + 2]){
				varAbs = preValue[] - hsv[p + 2];//絶対値を決定
			}else{
				varAbs = hsv[p + 2] - preValue[];//絶対値を決定
			}
			preValue[] = hsv[p + 2];//明度配列に現在の明度を格納
			//絶対値から増減割合を決定
			hsv[p + 2] = hsv[p + 2] * hoge;//明度を増減
			*/



			//HSVからRGBへ
			hoge = (hsv[p] / 60) % 6;
			f = (hsv[p] / 60) - (hsv[p] / 60);
			b = (hsv[p + 2] * (1 - (hsv[p + 1] / 255))) + 0.5;
			q = (hsv[p + 2] * (1 - (hsv[p + 1] / 255) * f)) + 0.5;
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


	//画像処理後
	img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
	img.draw(20, 330);//画像処理したモノを描画する
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