void Mini_Display() {
   display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Speed: "); display.print(DesiredSpeed); display.println("% ");
  display.print("Angle: "); display.println((int)angle);
  display.print("US:" ); display.print(uS / US_ROUNDTRIP_CM); display.println(" cm");
  // display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.display();
}
