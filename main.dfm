object MainFrm: TMainFrm
  Left = 816
  Top = 110
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsNone
  Caption = '[noname]'
  ClientHeight = 162
  ClientWidth = 200
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000000000000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000082000000000000000000
    0000000888888888880000000000000000000888888877877880000000000000
    000188877FFF77787F8880000000000000888877F700FFF87FF0880000000000
    0088777FF0000FF8FFF00880000000000888777FF0008FF17FF0008000000000
    088877FFF800FFF0FFF000880000000088777FFFFFFFFFF1FFF0000800000000
    8877FFFFFFFFFFF9FF000008800000088777FFFFFFFFFFF9F800000080000008
    8FFFFFFFFFFFFFF980000000800000088F7FFFFFFFFFFF890100000088000008
    8F7FFFFFFFFF000901000000800000088F7FFFFFFFF000090100000080000008
    8FFFFFFFF800000901000000800000088FFFFFFF800000090900000080000000
    87FFFFF700000009991000008000000088FFFFF0000000999990000880000000
    88FFFF70000009981988000800000000088FFF70000099000977008800000000
    0087FF700000990009F80880000000000088FFF00000991019F0881000000000
    000888F8001119999D1888000000000000008887800000099988000000000000
    0000008888100038880000000000000000000000888888880000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFFFFFFFFFFFFFFFFFFF3FFFFFE003FFFF8001FFFE00007FFC00003FFC00
    001FF800001FF800000FF000000FF0000007E0000007E0000007E0000003E000
    0007E0000007E0000007E0000007F0000007F0000007F000000FF800000FFC00
    001FFC00001FFE00003FFF0000FFFFC003FFFFF00FFFFFFFFFFFFFFFFFFF}
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnMouseDown = FormMouseDown
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object AniTmr: TTimer
    Interval = 10
    OnTimer = AniTmrTimer
  end
  object FrameCounter: TTimer
    OnTimer = FrameCounterTimer
    Left = 32
  end
  object RenderTmr: TTimer
    Interval = 30
    OnTimer = RenderTmrTimer
    Left = 64
  end
end