object FVirtualKeyboard: TFVirtualKeyboard
  Left = 0
  Top = 0
  Caption = 'FVirtualKeyboard'
  ClientHeight = 261
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Visible = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  DesignSize = (
    984
    261)
  TextHeight = 15
  object TouchKeyboard1: TTouchKeyboard
    Left = 0
    Top = 0
    Width = 985
    Height = 257
    Anchors = [akLeft, akTop, akRight, akBottom]
    GradientEnd = clSilver
    GradientStart = clGray
    Layout = 'Standard'
  end
end
