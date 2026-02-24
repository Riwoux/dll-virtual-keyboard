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
  OnDestroy = FormDestroy
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 24
    Width = 264
    Height = 13
    Caption = 'Click in the text area to test the keyboard:'
  end
  object Edit1: TEdit
    Left = 24
    Top = 43
    Width = 449
    Height = 21
    NumbersOnly = True
    TabOrder = 0
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 24
    Top = 80
    Width = 449
    Height = 21
    TabOrder = 1
    Text = 'Edit2'
  end
  object Button1: TButton
    Left = 72
    Top = 144
    Width = 337
    Height = 179
    Caption = 'Button1'
    TabOrder = 2
  end
end
