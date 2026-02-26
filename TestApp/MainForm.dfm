object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'Virtual Keyboard Test Application'
  ClientHeight = 355
  ClientWidth = 513
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Consolas'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  TextHeight = 13
  object Edit1: TEdit
    Left = 112
    Top = 152
    Width = 121
    Height = 21
    NumbersOnly = True
    TabOrder = 0
    Text = 'Edit1'
    OnEnter = TextControlEnter
  end
  object Edit2: TEdit
    Left = 248
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Edit2'
    OnEnter = TextControlEnter
  end
end
