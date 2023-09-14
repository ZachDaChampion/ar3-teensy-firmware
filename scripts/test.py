import flatbuffers
import fb.CobotMsgs.IncomingMessage as IncomingMessage
import fb.CobotMsgs.Request.Request as Request
import fb.CobotMsgs.Request.Init as Init
import fb.CobotMsgs.Request.Calibrate as Calibrate
import fb.CobotMsgs.Request.GoHome as GoHome
import fb.CobotMsgs.Request.RequestPayload as RequestPayload
import fb.CobotMsgs.Request.MoveTo as MoveTo
import fb.CobotMsgs.Request.MoveToEntry as MoveToEntry
import serial

CRC_TABLE = [
  0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
  0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
  0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
  0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
  0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
  0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
  0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
  0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
  0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
  0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
  0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
  0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
  0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
  0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
  0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
  0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
]

def crc8ccitt(data):
  val = 0
  for b in data:
    val = CRC_TABLE[(val ^ b) & 0xFF]
  return val & 0xFF

uuid = 0

def frame_msg(msg):
  header = [0x24, len(msg) & 0xFF, crc8ccitt(msg) & 0xFF]
  return bytes(header) + msg

def gen_init_msg(fw_version):
  builder = flatbuffers.Builder()
  Init.Start(builder)
  Init.AddExpectedFwVersion(builder, fw_version)
  init_msg = Init.End(builder)
  Request.Start(builder)
  Request.AddMessageId(builder, uuid)
  Request.AddPayloadType(builder, RequestPayload.RequestPayload().Init)
  Request.AddPayload(builder, init_msg)
  request = Request.End(builder)
  IncomingMessage.Start(builder)
  IncomingMessage.AddPayload(builder, request)
  incoming_message = IncomingMessage.End(builder)
  builder.Finish(incoming_message)
  return builder.Output()

def gen_calibrate(bitfield):
  builder = flatbuffers.Builder()
  Calibrate.Start(builder)
  Calibrate.AddJointsBitfield(builder, bitfield)
  calibrate_msg = Calibrate.End(builder)
  Request.Start(builder)
  Request.AddMessageId(builder, uuid)
  Request.AddPayloadType(builder, RequestPayload.RequestPayload().Calibrate)
  Request.AddPayload(builder, calibrate_msg)
  request = Request.End(builder)
  IncomingMessage.Start(builder)
  IncomingMessage.AddPayload(builder, request)
  incoming_message = IncomingMessage.End(builder)
  builder.Finish(incoming_message)
  return builder.Output()


def gen_home(bitfield):
  builder = flatbuffers.Builder()
  GoHome.Start(builder)
  GoHome.AddJointsBitfield(builder, bitfield)
  go_home_msg = GoHome.End(builder)
  Request.Start(builder)
  Request.AddMessageId(builder, uuid)
  Request.AddPayloadType(builder, RequestPayload.RequestPayload().GoHome)
  Request.AddPayload(builder, go_home_msg)
  request = Request.End(builder)
  IncomingMessage.Start(builder)
  IncomingMessage.AddPayload(builder, request)
  incoming_message = IncomingMessage.End(builder)
  builder.Finish(incoming_message)
  return builder.Output()

def gen_move_to(entries_list):
  builder = flatbuffers.Builder()
  MoveTo.StartEntriesVector(builder, len(entries_list))
  for entry in reversed(entries_list):
    MoveToEntry.CreateMoveToEntry(builder, entry[0], entry[1], entry[2])
  entries = builder.EndVector()
  MoveTo.Start(builder)
  MoveTo.AddEntries(builder, entries)
  move_to_msg = MoveTo.End(builder)
  Request.Start(builder)
  Request.AddMessageId(builder, uuid)
  Request.AddPayloadType(builder, RequestPayload.RequestPayload().MoveTo)
  Request.AddPayload(builder, move_to_msg)
  request = Request.End(builder)
  IncomingMessage.Start(builder)
  IncomingMessage.AddPayload(builder, request)
  incoming_message = IncomingMessage.End(builder)
  builder.Finish(incoming_message)

  return builder.Output()

try:
  ser = serial.Serial('COM5', 115200, timeout=1)
except:
  try:
    ser = serial.Serial('COM8', 115200, timeout=1)
  except:
    print('Failed to open serial port.')
    ser = None

while True:

  # Read all bytes from the serial port.
  if ser is not None:
    read = ser.read_all()
    print(read)
    print()

  # Parse a user message and execute it as a python command.
  user_input = input('>>> ')
  if user_input == '':
    continue
  if user_input == 'exit':
    break

  exec(f'msg = frame_msg({user_input})')

  # Print each byte of the message.
  for b in msg:
    print(hex(b)[2:].rjust(2, '0'), end=' ')
  print()
  print()

  # Send the message to the serial port.
  if ser is not None:
    ser.write(msg)
