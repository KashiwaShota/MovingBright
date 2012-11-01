#include "testApp.h"

ofVideoGrabber vidGrabber;
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
	vidGrabber.draw(20,20);//20,20����`�悷��
	
	//���݂̃t���[���̃s�N�Z���z��,RGB[width*height*3]�̃|�C���^��Ԃ��܂��B
	unsigned char * pixels = vidGrabber.getPixels();
	//�F���]����
	for(int i = 0; i < camHeight; i++){
		for(int j = 0; j < camWidth; j++){
			int p = i * camWidth * 3 + j * 3;
			pixels[p] = 255-pixels[p];
			pixels[p + 1] = 255-pixels[p + 1];
			pixels[p + 2] = 255-pixels[p + 2];
		}
	}
	//������̉摜�̕`��
	img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
	img.draw(20, 330);//20,330����摜�����������m��`�悷��
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