pushd
cd embeddedproto
protoc --plugin=protoc-gen-eams=protoc-gen-eams.bat -I ../proto --eams_out=../include/proto ../proto/main.proto
popd