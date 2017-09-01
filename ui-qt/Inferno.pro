TEMPLATE=subdirs
SUBDIRS=ToolLib/Match/ToolMatchLine  \
    ToolLib/Match/ToolMatchCircle \
    ToolLib/Match/ToolMatchBlob \
    Pretreatment \
    Relation \
    ToolLib/Match/ToolMatchBoundary \
    ToolLib/Match/ToolMatchBasePoint \
    ToolLib/Match/ToolMatchBaseline \
    ToolLib/Match/ToolMatchSkeleton \
    ToolLib/Measure/P2PDistance \
    ToolLib/Measure/P2LDistance \
    ToolLib/Measure/L2LDistance \
    ToolLib/Measure/L2LAngle \
    ToolLib/Measure/P2POffset \
    ToolLib/Measure/L2LCrossPoint \
    ToolLib/Measure/MiddleLine \
    ToolLib/Measure/VerticalPoint \
    ToolLib/Measure/P2PLine \
    ToolLib/Measure/P2PCenterPoint \
    ToolLib/Measure/PolygonCenter \
    DataOutput/IOOutput \
    DataOutput/IOTrigger \
    DataOutput/SerialPort \
    DataOutput/EthernetPort \
    Keyboard/FrmInputKeyBoard \
    DataOutput/UdpComm \
    DataOutput/UserDefined \
    ToolLib/Logic/LogicIoJump \
    DataOutput/Modbus \
    ToolLib/Logic/LogicCommandJump \
    DataOutput/MitFxPlc \
    ToolLib/Logic/LogicCondJump \
    ToolLib/Logic/LogicCmpJump \
    ToolLib/Logic/ToolLogicDataJudge \
    ToolLib/Logic/ToolLogicDelay \
    ToolLib/Logic/ToolLogicWorkOver \
    ToolLib/Detection/GrayStatistics \
    ToolLib/Logic/ToolLogicWorkOver \
    ToolLib/Detection/BlobCount \
    ToolLib/Detection/ToolColorArea \
    ToolLib/Detection/Contrast \
    ToolLib/Detection/MeanBrightness \
    ToolLib/Detection/ToolSpotFlaw \
    ToolLib/Detection/LineFlaw \
    ToolLib/Detection/ToolMonoArea \
    ToolLib/Detection/ContourPoints \
    InfernoUI \
    LearningDialog \
    ToolLib/Script/ToolScript \
    ToolLib/Calc/Statistic \
    ToolLib/Calc/Calculator \
    ToolLib/Measure/ToolWHMeasure \
    ToolLib/Match/ToolMatchSample \
    ToolLib/ScanCode/QrCode \
    ToolLib/Match/ToolMatchPolar \
    DataOutput/HansRobothProtocol \
    ToolLib/ScanCode/Barcode \
    ToolLib/Calc/ToolHomoCalc \
    ToolLib/Calc/ToolScaleCalc

CONFIG+=ordered
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
