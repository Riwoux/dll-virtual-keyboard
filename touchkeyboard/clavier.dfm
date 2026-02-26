object keyboard: Tkeyboard
  Left = 0
  Top = 0
  BorderIcons = [biMinimize, biMaximize]
  Caption = 'keyboard'
  ClientHeight = 300
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnKeyPress = TouchKeyboard1KeyPress
  TextHeight = 15
  object TouchKeyboard1: TTouchKeyboard
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 294
    Height = 294
    Align = alClient
    GradientEnd = clSilver
    GradientStart = clGray
    Layout = 'NumPad'
  end
end
