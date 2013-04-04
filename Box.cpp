#include <osg/Geode>
#include <osg/Geometry>
#include "dimensions.h"

osg::ref_ptr<osg::Geode> createBox(const osg::Vec3& center,float width,float height,float depth)
{
    int numTilesX = 10;
    int numTilesY = 10;
    
    osg::Vec3 v000(center - osg::Vec3(width*0.5f,depth*0.5f,height*0.5f));
    osg::Vec3 dx(osg::Vec3(width/((float)numTilesX),0.0,0.0f));
    osg::Vec3 dy(osg::Vec3(0.0f,depth/((float)numTilesY),0.0f));
    
    // fill in vertices for grid, note numTilesX+1 * numTilesY+1...
    osg::Vec3Array* coords = new osg::Vec3Array;
    for(int iy=0;iy<=numTilesY;++iy)
    {
        for(int ix=0;ix<=numTilesX;++ix)
        {
            coords->push_back(v000+dx*(float)ix+dy*(float)iy);
        }
    }
    
    //Just two colours - black and white.
    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); // white
    colors->push_back(osg::Vec4(0.0f,0.0f,0.0f,1.0f)); // black
    int numColors=colors->size();
    
    int numIndicesPerRow=numTilesX+1;
    osg::UByteArray* coordIndices = new osg::UByteArray; // assumes we are using less than 256 points...
    osg::UByteArray* colorIndices = new osg::UByteArray;
    for(int iy=0;iy<numTilesY;++iy)
    {
        for(int ix=0;ix<numTilesX;++ix)
        {
            // four vertices per quad.
            coordIndices->push_back(ix    +(iy+1)*numIndicesPerRow);
            coordIndices->push_back(ix    +iy*numIndicesPerRow);
            coordIndices->push_back((ix+1)+iy*numIndicesPerRow);
            coordIndices->push_back((ix+1)+(iy+1)*numIndicesPerRow);
            
            // one color per quad
            colorIndices->push_back((ix+iy)%numColors);
        }
    }
    
    // set up a single normal
    osg::Vec3Array* normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
    
    osg::ref_ptr<osg::Geometry> chessboard = new osg::Geometry;
    chessboard->setVertexArray(coords);
    chessboard->setVertexIndices(coordIndices);
    
    chessboard->setColorArray(colors);
    chessboard->setColorIndices(colorIndices);
    chessboard->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
    
    chessboard->setNormalArray(normals);
    chessboard->setNormalBinding(osg::Geometry::BIND_OVERALL);
    
    chessboard->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,coordIndices->size()));
    
	//set up environment (walls & ceiling)
	
	osg::Vec4Array* color = new osg::Vec4Array;
	color->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) ); // set color for walls & ceiling

	// create bart frame
	osg::ref_ptr<osg::Geometry> bBot = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, FRAME_WIDTH, 0.0f), 
		osg::Vec3(BART_WIDTH, 0.0f, 0.0f)	);
	bBot->setColorArray(color);
	osg::ref_ptr<osg::Geometry> bTop = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, -FRAME_WIDTH, 0.0f), 
		osg::Vec3(BART_WIDTH, 0.0f, 0.0f)	);
	bTop->setColorArray(color);
	osg::ref_ptr<osg::Geometry> bLeft = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, BART_HEIGHT, 0.0f)	);
	bLeft->setColorArray(color);
	osg::ref_ptr<osg::Geometry> bRight = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(-FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, BART_HEIGHT, 0.0f)	);
	bRight->setColorArray(color);
	
	// create gertjan front frame
	osg::ref_ptr<osg::Geometry> gfBot = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, BOT_FRAME_WIDTH), 
		osg::Vec3(GERTJAN_WIDTH, 0.0f, 0.0f)	);
	gfBot->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gfTop = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, -FRAME_WIDTH), 
		osg::Vec3(GERTJAN_WIDTH, 0.0f, 0.0f)	);
	gfTop->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gfLeft = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, 0.0f, GERTJAN_HEIGHT)	);
	gfLeft->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gfRight = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(-FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, 0.0f, GERTJAN_HEIGHT)	);
	gfRight->setColorArray(color);
	
	// create gertjan back frame
	osg::ref_ptr<osg::Geometry> gbBot = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, BOT_FRAME_WIDTH), 
		osg::Vec3(GERTJAN_WIDTH, 0.0f, 0.0f)	);
	gbBot->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gbTop = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, -FRAME_WIDTH), 
		osg::Vec3(GERTJAN_WIDTH, 0.0f, 0.0f)	);
	gbTop->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gbLeft = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, 0.0f, GERTJAN_HEIGHT)	);
	gbLeft->setColorArray(color);
	osg::ref_ptr<osg::Geometry> gbRight = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(-FRAME_WIDTH, 0.0f, 0.0f), 
		osg::Vec3(0.0f, 0.0f, GERTJAN_HEIGHT)	);
	gbRight->setColorArray(color);
	
	// create martijn front frame
	osg::ref_ptr<osg::Geometry> mfBot = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, FRAME_WIDTH), 
		osg::Vec3(0.0f, MARTIJN_WIDTH, 0.0f)	);
	mfBot->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mfTop = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, -FRAME_WIDTH), 
		osg::Vec3(0.0f, MARTIJN_WIDTH, 0.0f)	);
	mfTop->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mfLeft = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, FRAME_WIDTH, 0.0f), 
		osg::Vec3(0.0f, 0.0f, MARTIJN_HEIGHT)	);
	mfLeft->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mfRight = osg::createTexturedQuadGeometry(
		osg::Vec3(H_BOX_WIDTH, H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, -FRAME_WIDTH, 0.0f), 
		osg::Vec3(0.0f, 0.0f, MARTIJN_HEIGHT)	);
	mfRight->setColorArray(color);
	
	// create martijn back frame
	osg::ref_ptr<osg::Geometry> mbBot = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, FRAME_WIDTH), 
		osg::Vec3(0.0f, MARTIJN_WIDTH, 0.0f)	);
	mbBot->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mbTop = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, H_BOX_HEIGHT),
		osg::Vec3(0.0f, 0.0f, -FRAME_WIDTH), 
		osg::Vec3(0.0f, MARTIJN_WIDTH, 0.0f)	);
	mbTop->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mbLeft = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, -H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, FRAME_WIDTH, 0.0f), 
		osg::Vec3(0.0f, 0.0f, MARTIJN_HEIGHT)	);
	mbLeft->setColorArray(color);
	osg::ref_ptr<osg::Geometry> mbRight = osg::createTexturedQuadGeometry(
		osg::Vec3(-H_BOX_WIDTH, H_BOX_DEPTH, -H_BOX_HEIGHT),
		osg::Vec3(0.0f, -FRAME_WIDTH, 0.0f), 
		osg::Vec3(0.0f, 0.0f, MARTIJN_HEIGHT)	);
	mbRight->setColorArray(color);
	
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( bBot.get() );
	geode->addDrawable( bTop.get() );
	geode->addDrawable( bLeft.get() );
	geode->addDrawable( bRight.get() );
	geode->addDrawable( gfBot.get() );
	geode->addDrawable( gfTop.get() );
	geode->addDrawable( gfLeft.get() );
	geode->addDrawable( gfRight.get() );
	geode->addDrawable( gbBot.get() );
	geode->addDrawable( gbTop.get() );
	geode->addDrawable( gbLeft.get() );
	geode->addDrawable( gbRight.get() );
	geode->addDrawable( mfBot.get() );
	geode->addDrawable( mfTop.get() );
	geode->addDrawable( mfLeft.get() );
	geode->addDrawable( mfRight.get() );
	geode->addDrawable( mbBot.get() );
	geode->addDrawable( mbTop.get() );
	geode->addDrawable( mbLeft.get() );
	geode->addDrawable( mbRight.get() );
	geode->addDrawable( chessboard );
	
    return geode;
}