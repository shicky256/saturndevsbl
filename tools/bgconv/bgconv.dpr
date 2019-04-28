program bgconv;
uses
  Windows, SysUtils, VCL.Graphics;

var
  i,
  outType, //c file (0) or binary (1)
  fileCount:
  Integer;
  filename: String;
procedure printHelp;
begin
  WriteLn('Usage: bgconv [palette bitmap].bmp [outputfile]');
  WriteLn('Optional parameters:');
  WriteLn('-oc or -ob: output to c file or binary (default: c file)');
end;

//procedure outputC(var cFile: TextFile; varName: String; tiles: array of Uint16; palette: array of Uint32);
//var
//  i, j: Integer;
//begin
//  WriteLn(cFile, 'const Uint16 ', varName, '[] = {');
//  for i := 0 to Length(img) - 1 do
//  begin
//    for j := 0 to Length(img[0]) - 1 do
//    begin
//      if (j < Length(img[0]) - 1) or (i < Length(img) - 1) then
//        Write(cFile, img[i][j], ',')
//      else
//        Write(cFile, img[i][j]);
//    end;
//    Write(cFile, #13#10); //new line
//  end;
//  WriteLn(cFile, '};');
//end;

procedure handleImage(input: String; outType: Integer);
var
  img: TBitmap;
  imgPal: TMaxLogPalette;
  line: pByte;
  saturnTiles: array of Uint16;
  //Saturn palette format:
  //0123456789ABCDEF0123456789ABCDEF
  //RRRRRRRRGGGGGGGGBBBBBBBB00000000
  saturnPal: array of Uint32;
  i, j, count: Integer;
  r, g, b: Uint8;
  outFile: TextFile;
  varName: String;
begin
  AssignFile(outFile, 'out.c');
  ReWrite(outFile);
  img := TBitmap.Create;
  img.LoadFromFile(input);
  SetLength(saturnTiles, img.Height * img.Width);
  GetPaletteEntries(img.Palette, 0, 256, imgPal.palPalEntry);
  WriteLn('num entries: ', imgPal.palNumEntries);
  for i := 0 to 256 do
  begin
    WriteLn('r: ', imgPal.palPalEntry[i].peRed, 'g: ', imgPal.palPalEntry[i].peGreen,
      'b: ', imgPal.palPalEntry[i].peBlue);
  end;



  //if outType = 0 then
  //begin
  //  varName := copy(input[i], 0, pos('.', input[i]) - 1);
  //  outputC(outFile, varName, saturnImg);
  //end;
//  else
//    outputBin(saturnImg);
  img.Destroy;
  //end;
  CloseFile(outFile);
end;

begin
  //set up defaults
  outType := 0;
  if ParamCount > 0 then
  begin //process command line parameters
    for i := 1 to ParamCount do
    if paramstr(i)[1] = '-' then
    begin
      begin
        if paramstr(i)[2] = 'o' then
        begin
          if paramstr(i)[3] = 'c' then
            outType := 0
          else if paramstr(i)[3] = 'b' then
            outType := 1
          else
          begin
            printHelp;
            exit;
          end
        end
        else
        begin
          printHelp;
          exit;
        end;
      end;
    end
    else
    begin
      filename := paramstr(i);
    end;
  handleImage(filename, outType);
  end
  else
    printHelp;
end.



