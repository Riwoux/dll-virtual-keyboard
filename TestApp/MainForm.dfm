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
    Left = 8
    Top = 32
    Width = 121
    Height = 21
    NumbersOnly = True
    TabOrder = 0
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 152
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Edit2'
  end
  object Edit_Int1: TEdit_Int
    Left = 176
    Top = 248
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object Memo1: TMemo
    Left = 8
    Top = 80
    Width = 121
    Height = 81
    Lines.Strings = (
      'Memo1')
    TabOrder = 3
  end
end
