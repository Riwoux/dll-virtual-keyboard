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
  object MemoTest: TMemo
    Left = 40
    Top = 43
    Width = 450
    Height = 200
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'Test area for the virtual keyboard.'
      ''
      'Click the Show button to display the keyboard.')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object BtnShow: TButton
    Left = 24
    Top = 270
    Width = 150
    Height = 40
    Caption = 'Show Keyboard'
    TabOrder = 1
    OnClick = BtnShowClick
  end
  object BtnHide: TButton
    Left = 355
    Top = 270
    Width = 150
    Height = 40
    Caption = 'Hide Keyboard'
    TabOrder = 2
    OnClick = BtnHideClick
  end
  object Button1: TButton
    Left = 191
    Top = 270
    Width = 145
    Height = 40
    Caption = 'Show NumPad'
    TabOrder = 3
    OnClick = Button1Click
  end
end
