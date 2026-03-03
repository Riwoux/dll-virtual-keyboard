object FVirtualKeyboard: TFVirtualKeyboard
  Left = 0
  Top = 0
  Anchors = [akLeft, akTop, akRight, akBottom]
  Caption = 'FVirtualKeyboard'
  ClientHeight = 334
  ClientWidth = 937
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  DesignSize = (
    937
    334)
  TextHeight = 15
  object TouchKeyboard1: TTouchKeyboard
    Left = 0
    Top = 0
    Width = 938
    Height = 332
    Anchors = [akLeft, akTop, akRight, akBottom]
    GradientEnd = clSilver
    GradientStart = clGray
    Layout = 'NumPad'
  end
end
