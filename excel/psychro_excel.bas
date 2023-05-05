Attribute VB_Name = "Módulo1"
Declare Sub psychro_density Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_volume Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_enthalpy Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_relhum Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_dewpoint Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_wetbulb Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_humrat Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_molfrac Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_Z Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub psychro_efactor Lib "psychro.dll" (t As Double, p As Double, r As Double)
Declare Sub psychro_tsat Lib "psychro.dll" (t As Double, r As Double)
Declare Sub psychro_psat Lib "psychro.dll" (p As Double, r As Double)

Declare Sub iso_density Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_volume Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_enthalpy Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_relhum Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_dewpoint Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_wetbulb Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_humrat Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_molfrac Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_Z Lib "psychro.dll" (ch As Long, t As Double, umidade As Double, p As Double, r As Double)
Declare Sub iso_efactor Lib "psychro.dll" (t As Double, p As Double, r As Double)
Declare Sub iso_tsat Lib "psychro.dll" (t As Double, r As Double)
Declare Sub iso_psat Lib "psychro.dll" (p As Double, r As Double)

Function num(ch As String)
Select Case ch
Case "R"
    num = 0
Case "B"
    num = 1
Case "D"
    num = 2
Case "W"
    num = 3
Case "X"
    num = 4
End Select

End Function

Function DENSITY(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_density(num(ch), t, um, p, r)
DENSITY = r
End Function

Function VOLUME(ch As String, t As Double, um As Double, p As Double)
Dim r As Double

Call psychro_volume(num(ch), t, um, p, r)
VOLUME = r
End Function


Function ENTHALPY(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_enthalpy(num(ch), t, um, p, r)
ENTHALPY = r
End Function


Function RELHUM(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_relhum(num(ch), t, um, p, r)
RELHUM = r
End Function

Function dewpoint(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_dewpoint(num(ch), t, um, p, r)
dewpoint = r
End Function

Function wetbulb(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_wetbulb(num(ch), t, um, p, r)
wetbulb = r
End Function

Function humrat(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_humrat(num(ch), t, um, p, r)
humrat = r
End Function

Function molfrac(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_molfrac(num(ch), t, um, p, r)
molfrac = r
End Function


Function Z(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call psychro_Z(num(ch), t, um, p, r)
Z = r
End Function

Function efactor(t As Double, p As Double)
Dim r As Double
Call psychro_efactor(t, p, r)
efactor = r
End Function

Function psat(t As Double)
Dim r As Double
Call psychro_psat(t, r)
psat = r
End Function

Function tsat(p As Double)
Dim r As Double
Call psychro_tsat(p, r)
tsat = r
End Function






'////////////////////////////////////////////////////////////////////
'/// GIACOMO
Function DENSITY_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_density(num(ch), t, um, p, r)
DENSITY_iso = r
End Function

Function VOLUME_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double

Call iso_volume(num(ch), t, um, p, r)
VOLUME_iso = r
End Function


Function ENTHALPY_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_enthalpy(num(ch), t, um, p, r)
ENTHALPY_iso = r
End Function


Function RELHUM_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_relhum(num(ch), t, um, p, r)
RELHUM_iso = r
End Function

Function dewpoint_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_dewpoint(num(ch), t, um, p, r)
dewpoint_iso = r
End Function

Function wetbulb_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_wetbulb(num(ch), t, um, p, r)
wetbulb_iso = r
End Function

Function humrat_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_humrat(num(ch), t, um, p, r)
humrat_iso = r
End Function

Function molfrac_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_molfrac(num(ch), t, um, p, r)
molfrac_iso = r
End Function


Function Z_iso(ch As String, t As Double, um As Double, p As Double)
Dim r As Double
Call iso_Z(num(ch), t, um, p, r)
Z_iso = r
End Function

Function efactor_iso(t As Double, p As Double)
Dim r As Double
Call iso_efactor(t, p, r)
efactor_iso = r
End Function

Function psat_iso(t As Double)
Dim r As Double
Call iso_psat(t, r)
psat_iso = r
End Function

Function tsat_iso(p As Double)
Dim r As Double
Call iso_tsat(p, r)
tsat_iso = r
End Function

Sub teste()
Dim r As Double

r = VOLUME("B", 20, 23, 101.325)


r = DENSITY("R", 20, 1, 101.325)
r = RELHUM("R", 20, 1, 101.325)
r = wetbulb("R", 20, 1, 101.325)
r = dewpoint("R", 20, 1, 101.325)
r = ENTHALPY("R", 20, 1, 101.325)
r = humrat("R", 20, 1, 101.325)
r = molfrac("R", 20, 1, 101.325)
r = Z("R", 20, 1, 101.325)
r = efactor(20, 101.325)
r = tsat(3)
r = psat(20)


rr = r * 1#

End Sub

