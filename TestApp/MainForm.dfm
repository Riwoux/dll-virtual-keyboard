object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'Test Application - Clavier Virtuel DLL'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 24
    Width = 295
    Height = 13
    Caption = 'Cliquez dans la zone de texte ci-dessous pour tester le clavier:'
  end
  object LabelStatus: TLabel
    Left = 24
    Top = 408
    Width = 111
    Height = 13
    Caption = #201'tat: Clavier masqu'#233
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object MemoTest: TMemo
    Left = 24
    Top = 48
    Width = 577
    Height = 257
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'Zone de test pour le clavier virtuel.'
      ''
      'Cliquez sur un des boutons ci-dessous pour afficher le '
      'clavier.')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object BtnShowSimple: TButton
    Left = 24
    Top = 328
    Width = 169
    Height = 41
    Caption = 'Afficher Clavier Simple'
    TabOrder = 1
    OnClick = BtnShowSimpleClick
  end
  object BtnShowWithNumpad: TButton
    Left = 216
    Top = 328
    Width = 185
    Height = 41
    Caption = 'Afficher Clavier avec Pav'#233
    TabOrder = 2
    OnClick = BtnShowWithNumpadClick
  end
  object BtnHide: TButton
    Left = 424
    Top = 328
    Width = 177
    Height = 41
    Caption = 'Masquer Clavier'
    TabOrder = 3
    OnClick = BtnHideClick
  end
end
