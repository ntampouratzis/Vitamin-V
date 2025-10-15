package HLANode;

simple Txc0
{
	parameters:
		double RXPacketTime = default(0.000001);
		int nodeNo = default(0);
		bool sendInitialMessage = default(false);

		@display("i=block/routing");
	gates:
		inout gate;
}
simple Txc1 extends Txc0
{
		parameters:
		RXPacketTime = default(0.000001);
		nodeNo = default(1);

		sendInitialMessage = default(false);
		@display("i=block/routing");
}
//simple Txc2 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(2);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc3 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(3);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc4 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(4);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc5 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(5);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc6 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(6);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc7 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(7);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc8 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(8);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc9 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(9);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc10 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(10);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc11 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(11);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc12 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(12);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc13 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(13);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc14 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(14);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc15 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(15);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//
//
//
//
//
//
//simple Txc16 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(16);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc17 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(17);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc18 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(18);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc19 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(19);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc20 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(20);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc21 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(21);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc22 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(22);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc23 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(23);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc24 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(24);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc25 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(25);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc26 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(26);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc27 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(27);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc28 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(28);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc29 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(29);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//simple Txc30 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(30);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}
//
//simple Txc31 extends Txc0
//{
//		parameters:
//		RXPacketTime = default(0.000001);
//		nodeNo = default(31);
//
//		sendInitialMessage = default(false);
//		@display("i=block/routing");
//}


simple SyncNode
{
	parameters:
		int NumberOfHLANodes = default(2);
		double SynchTime = default(0.000001);

		bool sendInitialMessage = default(false);
		@display("i=block/routing");
	gates:
		input in;
		output out;
}
