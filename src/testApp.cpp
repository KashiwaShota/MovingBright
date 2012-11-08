#include "testApp.h"

ofVideoGrabber vidGrabber;
unsigned char hsv[923520];//HSV�̔z���錾(int = hsv[p])
/*
hsv[p] = �F��(hus)
hsv[p + 1] = �ʓx(saturation)
hsv[p + 2] = ���x(value)
*/
/*
int max, min;//�ő�l�ƍŏ��l���i�[
���ꂾ�������Ő錾����Ƃ����܂��ȕϐ����ƌ�����
*/
unsigned char preValue[307200];//�O�t���[�����x���̔z���錾(640 * 480 = 307,200)
float varAbs;//��Βl���i�[
//HSV����RGB�֕ϊ����Ɏg�p����ϐ�
float f;
int hi, b, q, t;
ofImage img;
int camWidth, camHeight;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);//RGB�w�i�F
	ofEnableSmoothing();//�X���[�W���O�J�n
	ofSetFrameRate(60);//�t���[�����[�g�ݒ�
	//�L���v�`������摜�̃T�C�Y���w��
	camWidth = 640;//�L���v�`����ʂ̕�
	camHeight = 480;//�L���v�`����ʂ̍���
	vidGrabber.setVerbose(true);//�g�p�\�̃f�o�C�X��T��
	vidGrabber.initGrabber(camWidth, camHeight);//�C���^�[�t�F�C�X���f�o�b�N�ɖ𗧂�
}

//--------------------------------------------------------------
void testApp::update(){
	//�L���v�`������
	vidGrabber.grabFrame();//sequence grabbe����V�����f�[�^�𓾂�ׂɒ���I�ɌĂяo��
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);//�`��F(��)
	vidGrabber.draw(0,0);//���f����`�悷��
	//���݂̃t���[���̃s�N�Z���z��,RGB[width*height*3]�̃|�C���^��Ԃ�
	unsigned char * pixels = vidGrabber.getPixels();
	for(int i = 0; i < camHeight; i++){
		for(int j = 0; j < camWidth; j++){
			int p = i * camWidth * 3 + j * 3;
			//RGB����HSV��
			int max, min;//�ő�l�ƍŏ��l���i�[
			//�ő�l(max)�̌���
			max = max3(pixels[p], pixels[p + 1], pixels[p + 2]);
			//�ŏ��l(min)�̌���
			min = min3(pixels[p], pixels[p + 1], pixels[p + 2]);
			//�F��(hsv[p])�̌���
			if(max == min){
				hsv[p] = 0;
			}else if(max == pixels[p]){
				hsv[p] = (60 * (pixels[p + 1] - pixels[p + 2]) / (max - min) + 360) % 360;
			}else if(max == pixels[p + 1]){
				hsv[p] = (60 * (pixels[p + 2] - pixels[p]) / (max - min)) + 120;
			}else if(max == pixels[p + 2]){
				hsv[p] = (60 * (pixels[p] - pixels[p + 1]) / (max - min)) + 240;
			}
			//�ʓx(hsv[p + 1])�̌���
			if(max == 0){
				hsv[p + 1] = 0;
			}else{
				hsv[p + 1] = (255 * ((max - min) / max));
			}
			//���x(hsv[p + 2])�̌���
			hsv[p + 2] = max;



			//HSV�Ɏ��������
			//hsv[p + 1] = 100;//�F�ʂ�0�ɂ��ă��m�N����
			//�O�t���[���ƌ��݃t���[���̖��x��r
			/*
			//���x�z��̊i�[����ꏊ�����߂�
			if(preValue[] >= hsv[p + 2]){
				varAbs = preValue[] - hsv[p + 2];//��Βl������
			}else{
				varAbs = hsv[p + 2] - preValue[];//��Βl������
			}
			preValue[] = hsv[p + 2];//���x�z��Ɍ��݂̖��x���i�[
			//��Βl���瑝������������
			hsv[p + 2] = hsv[p + 2] * hoge;//���x�𑝌�
			*/


			
			//HSV����RGB��
			hi = (hsv[p] / 60) % 6;
			f = (hsv[p] / 60) - floor(hsv[p] / 60);
			b = round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f)));//off�����F�o��
			q = round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f) * f));//off���w�i���m�N��
			t = round(hsv[p + 2] * (1.0f - (hsv[p + 1] / 255.0f) * (1.0f - f)));//off���w�i���m�N��
			//�ꍇ�ɍ��킹��RGB�����肷��
			switch(hi){
				case 0:
					pixels[p] = hsv[p + 2];
					pixels[p + 1] = t;
					pixels[p + 2] = b;
					break;
				case 1:
					pixels[p] = q;
					pixels[p + 1] = hsv[p + 2];
					pixels[p + 2] = b;
					break;
				case 2:
					pixels[p] = b;
					pixels[p + 1] = hsv[p + 2];
					pixels[p + 2] = t;
					break;
				case 3:
					pixels[p] = b;
					pixels[p + 1] = q;
					pixels[p + 2] = hsv[p + 2];
					break;
				case 4:
					pixels[p] = t;
					pixels[p + 1] = b;
					pixels[p + 2] = hsv[p + 2];
					break;
				case 5:
					pixels[p] = hsv[p + 2];
					pixels[p + 1] = b;
					pixels[p + 2] = q;
					break;
			}
			
			
		}
	}


	//�摜������
	img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
	img.draw(640, 0);//�摜�����������m��`�悷��
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

//--------------------------------------------------------------
//Math�֐�

//�ő�l
int testApp::max2(int a, int b){
	return (a < b) ? b : a;
}
int testApp::max3(int a, int b, int c){
	return max2(max2(a, b), c);
}

//�ŏ��l
int testApp::min2(int a, int b){
	return (a < b) ? a : b;
}
int testApp::min3(int a, int b, int c){
	return min2(min2(a, b), c);
}

//�؎̂�
float testApp::floor(float a){
	int b = a;
	return b;
}

//���ϒl
float testApp::round(float a){
	int round;
	int decimalPoint = a * 10;//�����_��1�ʂ��J��グ��
	decimalPoint = decimalPoint % 10;//�]��Ƃ��ČJ��グ�������_��1�ʂ��o��
	float mod = decimalPoint / 10;//�]���10�Ŋ����ď����_��1�ʂɖ߂�
	if(mod > 0.4){
		round = a + 1;
	}else{
		round = a;
	}
	return round;
}