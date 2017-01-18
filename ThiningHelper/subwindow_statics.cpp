#include "subwindow_statics.h"
#include "includes.h"
#include <staticsInfo.h> 
#include <qfile.h>
#include <qfiledialog.h>

extern int EndPointNum;//���صĶ˵���Ŀ
extern int TriplePointNum;
extern cv::Mat src_thinned;
cv::Mat src_thinned_End_count;
cv::Mat src_thinned_Triple_count;

subwindow_statics::subwindow_statics(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	labelName_endPoint = new QLabel("End Point Num:", this);
	labelName_endPoint->setStyleSheet("font-size:15px;color:light-red;font-weight:bold;font-syle:");
	
	EndPointNum = returnEndCount(src_thinned, src_thinned_End_count); //�˴��и��� 2016.12.5
	QString qstring_EndPointNum = QString::number(EndPointNum, 10);
	label_endPointNum = new QLabel(qstring_EndPointNum, this);
	qDebug("!!!------ in subwindow----!!!end point num %d", EndPointNum);

	labelName_triplePointNum = new QLabel("Triple Point Num:", this);
	labelName_triplePointNum->setStyleSheet("font-size:15px;color:light-red;font-weight:bold;font-syle:");
	//QString qstring_EndPointNum = QString::number(EndPointNum, 10);

	//TriplePointNum = returnTripleCount(src_thinned, src_thinned_Triple_count);//�˴�src_thining��Ӧ�ô���һ����ʼ����Ϊ��һ���Ѿ������˱�ǣ�����
	QString qstring_TriplePointNum = QString::number(TriplePointNum, 10);
	label_triplePointNum = new QLabel(qstring_TriplePointNum, this);
	qDebug("%%%____________triple point num %d", TriplePointNum);

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(labelName_endPoint);
	layout1->addWidget(label_endPointNum);

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(labelName_triplePointNum);
	layout2->addWidget(label_triplePointNum);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(layout1);
	mainLayout->addLayout(layout2);

	//show layout 
	widget = new QWidget();
//	widget->setLayout(mainLayout);

	setLayout(mainLayout);
//	this->resize(255, 20);
	
	this->setWindowTitle("Statics Info");
	this->setMaximumSize(250, 100);
	this->setMinimumSize(250, 100);
}

subwindow_statics::~subwindow_statics()
{

}
/*
void on_actionSave_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this,tr("Save File"), QString(), tr("Text Files(*.txt);;c++ Files(*.cpp *.h);;Jsp Files(*.jsp)"));
	if (!filename.isEmpty())
	{
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly))
		{
		}
		else
		{
			QTextStream stream(&file);
			stream << ui->textEdit->toPlainText();
			stream.flush();
			file.close();
		}
	}
}
*/