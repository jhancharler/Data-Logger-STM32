SamacSys ECAD Model
14859557/1120083/2.50/3/3/Undefined or Miscellaneous

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r610_570"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 5.700) (shapeHeight 6.100))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(padStyleDef "c1790"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 17.900) (shapeHeight 17.900))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "BATHLD003SMT" (originalName "BATHLD003SMT")
		(multiLayer
			(pad (padNum 1) (padStyleRef r610_570) (pt -12.900, 0.000) (rotation 0))
			(pad (padNum 2) (padStyleRef r610_570) (pt 12.900, 0.000) (rotation 0))
			(pad (padNum 3) (padStyleRef c1790) (pt 0.000, 0.000) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0.000, 0.575) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -16.75 11.5) (pt 16.75 11.5) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 16.75 11.5) (pt 16.75 -10.35) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 16.75 -10.35) (pt -16.75 -10.35) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -16.75 -10.35) (pt -16.75 11.5) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 4 10.45) (pt -4 10.45) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -4 10.45) (pt -10.55 4.5) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -10.55 4.5) (pt -10.55 -9.35) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -10.55 -9.35) (pt 10.55 -9.35) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 10.55 -9.35) (pt 10.55 4.5) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 10.55 4.5) (pt 4 10.5) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -10.55 2.55) (pt -15.2 2.55) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -15.2 2.55) (pt -15.2 -2.55) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -15.2 -2.55) (pt -10.55 -2.55) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 10.55 2.55) (pt 15.2 2.55) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 15.2 2.55) (pt 15.2 -2.55) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 15.2 -2.55) (pt 10.55 -2.55) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -10.55 3.575) (pt -10.55 4.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -10.55 4.5) (pt -4 10.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -4 10.45) (pt 4 10.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 4 10.45) (pt 10.55 4.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 10.55 4.5) (pt 10.55 3.575) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 10.55 -3.625) (pt 10.55 -9.35) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 10.55 -9.35) (pt -10.55 -9.35) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -10.55 -9.35) (pt -10.55 -3.625) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -16.2 0.175) (pt -16.2 0.175) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -16.15, 0.175) (radius 0.049999999999999) (startAngle 180.0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -16.1 0.175) (pt -16.1 0.175) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -16.15, 0.175) (radius 0.049999999999999) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "BAT-HLD-003-SMT" (originalName "BAT-HLD-003-SMT")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -300 mils) (width 6 mils))
		(line (pt 600 mils -300 mils) (pt 200 mils -300 mils) (width 6 mils))
		(line (pt 200 mils -300 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "BAT-HLD-003-SMT" (originalName "BAT-HLD-003-SMT") (compHeader (numPins 3) (numParts 1) (refDesPrefix U)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "BAT-HLD-003-SMT"))
		(attachedPattern (patternNum 1) (patternName "BATHLD003SMT")
			(numPads 3)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
			)
		)
		(attr "Mouser Part Number" "712-BAT-HLD-003-SMT")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Linx-Technologies/BAT-HLD-003-SMT?qs=TuK3vfAjtkVRZQIT6eTqjQ%3D%3D")
		(attr "Manufacturer_Name" "Linx Technologies")
		(attr "Manufacturer_Part_Number" "BAT-HLD-003-SMT")
		(attr "Description" "Coin Cell Battery Holders Holder for 2016, 2020, 2025 and 2032 Batteries, Surface Mount, Bulk Packaging")
		(attr "Datasheet Link" "https://linxtechnologies.com/wp/wp-content/uploads/bat-hld-003-smt-ds.pdf")
		(attr "Height" "4.2 mm")
	)

)