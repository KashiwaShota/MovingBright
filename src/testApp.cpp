#include "testApp.h"

ofVideoGrabber vidGrabber;
int hsv[405000];//HSV�̔z���錾(int = hsv[p])
/*
hsv[p] = �F��(hus)
hsv[p + 1] = �ʓx(saturation)
hsv[p + 2] = ���x(value)
*/
/*
int max, min;//�ő�l�ƍŏ��l���i�[
���ꂾ�������Ő錾����Ƃ����܂��ȕϐ����ƌ�����
*/
int preValue[];//�O�t���[�����x���̔z���錾
float varAbs;//��Βl���i�[
//HSV����RGB�֕ϊ����Ɏg�p����ϐ�
float f;
int hoge, b, q, t;
ofImage img;
int camWidth, camHeight;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);//RGB�w�i�F
	ofEnableSmoothing();//�X���[�W���O�J�n
	ofSetFrameRate(10);//�t���[�����[�g�ݒ�
	//�L���v�`������摜�̃T�C�Y���w��
	camWidth = 450;//�L���v�`����ʂ̕�
	camHeight = 300;//�L���v�`����ʂ̍���
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
	vidGrabber.draw(20,20);//���f����`�悷��
	//���݂̃t���[���̃s�N�Z���z��,RGB[width*height*3]�̃|�C���^��Ԃ�
	unsigned char * pixels = vidGrabber.getPixels();
	for(int i = 0; i < camHeight; i++){
		for(int j = 0; j < camWidth; j++){
			int p = i * camWidth * 3 + j * 3;
			//RGB����HSV��
			int max, min;//�ő�l�ƍŏ��l���i�[
			//�ő�l(max)�̌���
			if(pixels[p] >= pixels[p + 1]){
				max = pixels[p];
			}else{
				max = pixels[p + 1];
			}
			if(pixels[p + 2] > max){
				max = pixels[p + 2];
			}
			//�ŏ��l(min)�̌���
			if(pixels[p] <= pixels[p + 1]){
				min = pixels[p];
			}else{
				min = pixels[p + 1];
			}
			if(pixels[p + 2] < min){
				max = pixels[p + 2];
			}
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
			hsv[p + 1] = 0;//�F�ʂ�0�ɂ��ă��m�N����
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
			hoge = (hsv[p] / 60) % 6;
			f = (hsv[p] / 60) - (hsv[p] / 60);
			b = (hsv[p + 2] * (1 - (hsv[p + 1] / 255))) + 0.5;
			q = (hsv[p + 2] * (1 - (hsv[p + 1] / 255) * f)) + 0.5;
			t = (hsv[p + 2] * (1 - (hsv[p + 1] / 255) * (1 - f))) + 0.5;
			//�ꍇ�ɍ��킹��RGB�����肷��
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


	//�摜������
	img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
	img.draw(20, 330);//�摜�����������m��`�悷��
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