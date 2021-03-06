#include "nextframecommand.h"

NextFrameCommand::NextFrameCommand(QObject *parent) :
    GitlAbstractCommand(parent)
{

}

bool NextFrameCommand::execute( GitlCommandParameter &rcInputArg, GitlCommandParameter& rcOutputArg )
{
    ModelLocator* pModel = ModelLocator::getInstance();

    int iCurBufPoc = pModel->getFrameBuffer().getPoc();
    int iNextPoc = iCurBufPoc+1;
    if( iNextPoc >= pModel->getSequenceManager().getCurrentSequence().getTotalFrames())
        return false;

    QPixmap* pcFramePixmap = pModel->getFrameBuffer().getFrame(iNextPoc);   ///< Read Frame Buffer
    pcFramePixmap = pModel->getDrawEngine().drawFrame(&(pModel->getSequenceManager().getCurrentSequence()), iNextPoc, pcFramePixmap);  ///< Draw Frame Buffer

    ///
    rcOutputArg.setParameter("picture",  QVariant::fromValue((void*)(pcFramePixmap)));
    rcOutputArg.setParameter("current_frame_poc", iNextPoc );
    rcOutputArg.setParameter("total_frame_num", pModel->getSequenceManager().getCurrentSequence().getTotalFrames());

    return true;
}
