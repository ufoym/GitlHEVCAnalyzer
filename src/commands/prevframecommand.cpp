#include "prevframecommand.h"
#include <QPixmap>
PrevFrameCommand::PrevFrameCommand(QObject *parent) :
    GitlAbstractCommand(parent)
{
}

bool PrevFrameCommand::execute( GitlCommandParameter& rcInputArg, GitlCommandParameter& rcOutputArg )
{
    ModelLocator* pModel = ModelLocator::getInstance();

    int iCurBufPoc = pModel->getFrameBuffer().getPoc();
    int iPredPoc = iCurBufPoc - 1;
    if( iPredPoc < 0)
        return false;

    QPixmap* pcFramePixmap = pModel->getFrameBuffer().getFrame(iPredPoc);   ///< Read Frame Buffer
    pcFramePixmap = pModel->getDrawEngine().drawFrame(&(pModel->getSequenceManager().getCurrentSequence()), iPredPoc, pcFramePixmap);  ///< Draw Frame Buffer

    ///
    rcOutputArg.setParameter("picture",  QVariant::fromValue((void*)(pcFramePixmap)));
    rcOutputArg.setParameter("current_frame_poc", iPredPoc);
    rcOutputArg.setParameter("total_frame_num", pModel->getSequenceManager().getCurrentSequence().getTotalFrames());

    return true;
}
